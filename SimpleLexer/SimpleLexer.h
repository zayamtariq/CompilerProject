#include "Data.h"

static int next(void); 

static void putback(int c); 

static int skip(void); 

int scan(struct Token *t); 

static int readInt(int c); 