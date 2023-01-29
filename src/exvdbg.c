#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <linux/socket.h>
#include <arpa/inet.h>

#include "exvdbg.h"

#define UDP_SEND_PORT 8765

static void sendto_daemon(ExDbgConext *ctx, char *strbuf, int len)
{
    struct sockaddr_in sockadr;
    memset(&sockadr, 0, sizeof(sockadr));

    sockadr.sin_family = AF_INET;
    sockadr.sin_port = htons(UDP_SEND_PORT);
    sockadr.sin_addr.s_addr = inet_addr("127.0.0.1");

    socklen_t slen = sizeof(sockadr);
    ssize_t sendlen = sendto(ctx->sock, strbuf,
                             strlen(strbuf), 0,
                             (struct sockaddr *)&sockadr, slen);
    if (sendlen < 1){
        fprintf(stderr, "sendto daemon fail..\n");
    } else {
        // fprintf(stderr, strbuf, len);
    }
}

void exvdbg_streamlogbox_new(ExDbgConext *ctx,
                             char *eid,
                             int xpos,
                             int ypos,
                             int width,
                             int height)
{
    sprintf(ctx->str_buildbuf,
            "{"
            "\"request-type\" : \"stream_logbox\","
            "\"session-id\" : \"%s\","
            "\"elem-id\" : \"%s\","
            "\"pos-x\" : \"%d\","
            "\"pos-y\" : \"%d\","
            "\"width\" : \"%d\","
            "\"height\" : \"%d\""
            "}", ctx->session_id, eid, xpos, ypos, width, height);
    sendto_daemon(ctx, ctx->str_buildbuf, strlen(ctx->str_buildbuf));
}

void exvdbg_streamlog(ExDbgConext *ctx, char *eid, char *log)
{
    sprintf(ctx->str_buildbuf,
            "{"
            "\"request-type\" : \"stream_log\","
            "\"session-id\" : \"%s\","
            "\"elem-id\" : \"%s\","
            "\"log\" : \"%s\\n\""
            "}", ctx->session_id, eid, log
    );
    sendto_daemon(ctx, ctx->str_buildbuf, strlen(ctx->str_buildbuf));
}

#define exvdbg_streamlogf(ctx, eid, ...) do {\
    sprintf(ctx->templgbuf, __VA_ARGS__);           \
    exvdbg_streamlog((ctx), (eid), ctx->templgbuf); \
} while(0);

/*
@session_id -> Should be shorter than 100bytes
*/
ExDbgConext *exvdbg_new(char *session_id)
{
    ExDbgConext *ctx = malloc(sizeof(ExDbgConext));
    strcpy(ctx->session_id, session_id);

    /* Open socket */
    ctx->sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (ctx->sock < 1)
    {
        fprintf(stderr, "socket() failed\n");
    }
    else
    {
        fprintf(stderr, "socket() : %d\n", ctx->sock);
    }
    return ctx;
}

void exvdbg_finalize(ExDbgConext *ctx)
{
    if (ctx)
        free(ctx);
}