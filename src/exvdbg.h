#ifndef EXVDBG_H
#define EXVDBG_H

typedef struct ExDbgConext{
    int sock;
    char session_id[100];
    char str_buildbuf[4000];
    char templgbuf[4000];
}ExDbgConext;

void exvdbg_streamlogbox_new(ExDbgConext *ctx,
                             char *eid,
                             int xpos,
                             int ypos,
                             int width,
                             int height);

void exvdbg_streamlog(ExDbgConext *ctx, char *eid, char *log);

#define exvdbg_streamlogf(ctx, eid, ...) do {\
    sprintf(ctx->templgbuf, __VA_ARGS__);           \
    exvdbg_streamlog((ctx), (eid), ctx->templgbuf); \
} while(0);

ExDbgConext *exvdbg_new(char *session_id);

void exvdbg_finalize(ExDbgConext *ctx);

#endif