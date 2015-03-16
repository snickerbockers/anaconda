static bool collide_sprite_sprite(CollisionBase * in_a, CollisionBase * in_b, int w, int h, int offx1, int offy1, int offx2, int offy2)
{
    SpriteCollision * a = (SpriteCollision*)in_a;
    SpriteCollision * b = (SpriteCollision*)in_b;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    else {
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool collide_sprite_tsprite(CollisionBase * in_a, CollisionBase * in_b, int w, int h, int offx1, int offy1, int offx2, int offy2)
{
    SpriteCollision * a = (SpriteCollision*)in_a;
    SpriteCollision * b = (SpriteCollision*)in_b;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    offx2 += b->x_t;
    offy2 += b->y_t;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        if (b->flags & BOX_COLLISION) {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!(((unsigned char*)(b_arr + b_yy * b_width + b_xx))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!b_alpha.get(b_yy * b_width + b_xx))
                        continue;
                    return true;
                }
            }
        }
    }
    else {
        if (b->flags & BOX_COLLISION) {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    return true;
                }
            }
        }
        else if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!(((unsigned char*)(b_arr + b_yy * b_width + b_xx))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!b_alpha.get(b_yy * b_width + b_xx))
                        continue;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool collide_sprite_background(CollisionBase * in_a, CollisionBase * in_b, int w, int h, int offx1, int offy1, int offx2, int offy2)
{
    SpriteCollision * a = (SpriteCollision*)in_a;
    BackgroundItem * b = (BackgroundItem*)in_b;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    offx2 += b->src_x;
    offy2 += b->src_y;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    else {
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool collide_sprite_backdrop(CollisionBase * in_a, CollisionBase * in_b, int w, int h, int offx1, int offy1, int offx2, int offy2)
{
    SpriteCollision * a = (SpriteCollision*)in_a;
    BackdropCollision * b = (BackdropCollision*)in_b;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    else {
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool collide_sprite_box(CollisionBase * in_a, int w, int h, int offx1, int offy1)
{
    SpriteCollision * a = (SpriteCollision*)in_a;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                    continue;
                return true;
            }
        }
    }
    else {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                    continue;
                return true;
            }
        }
    }
    return false;
}

static bool collide_tsprite_sprite(CollisionBase * in_a, CollisionBase * in_b, int w, int h, int offx1, int offy1, int offx2, int offy2)
{
    SpriteCollision * a = (SpriteCollision*)in_a;
    SpriteCollision * b = (SpriteCollision*)in_b;
    offx1 += a->x_t;
    offy1 += a->y_t;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (a->flags & BOX_COLLISION) {
        int a_height = a_img->height;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    else if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        int a_height = a_img->height;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + a_yy * a_width + a_xx))[3] != 0))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + a_yy * a_width + a_xx))[3] != 0))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    else {
        int a_height = a_img->height;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!a_alpha.get(a_yy * a_width + a_xx))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!a_alpha.get(a_yy * a_width + a_xx))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool collide_tsprite_tsprite(CollisionBase * in_a, CollisionBase * in_b, int w, int h, int offx1, int offy1, int offx2, int offy2)
{
    SpriteCollision * a = (SpriteCollision*)in_a;
    SpriteCollision * b = (SpriteCollision*)in_b;
    offx1 += a->x_t;
    offy1 += a->y_t;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    offx2 += b->x_t;
    offy2 += b->y_t;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (a->flags & BOX_COLLISION) {
        int a_height = a_img->height;
        if (b->flags & BOX_COLLISION) {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    return true;
                }
            }
        }
        else if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!(((unsigned char*)(b_arr + b_yy * b_width + b_xx))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!b_alpha.get(b_yy * b_width + b_xx))
                        continue;
                    return true;
                }
            }
        }
    }
    else if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        int a_height = a_img->height;
        if (b->flags & BOX_COLLISION) {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + a_yy * a_width + a_xx))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + a_yy * a_width + a_xx))[3] != 0))
                        continue;
                    if (!(((unsigned char*)(b_arr + b_yy * b_width + b_xx))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + a_yy * a_width + a_xx))[3] != 0))
                        continue;
                    if (!b_alpha.get(b_yy * b_width + b_xx))
                        continue;
                    return true;
                }
            }
        }
    }
    else {
        int a_height = a_img->height;
        if (b->flags & BOX_COLLISION) {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!a_alpha.get(a_yy * a_width + a_xx))
                        continue;
                    return true;
                }
            }
        }
        else if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!a_alpha.get(a_yy * a_width + a_xx))
                        continue;
                    if (!(((unsigned char*)(b_arr + b_yy * b_width + b_xx))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!a_alpha.get(a_yy * a_width + a_xx))
                        continue;
                    if (!b_alpha.get(b_yy * b_width + b_xx))
                        continue;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool collide_tsprite_background(CollisionBase * in_a, CollisionBase * in_b, int w, int h, int offx1, int offy1, int offx2, int offy2)
{
    SpriteCollision * a = (SpriteCollision*)in_a;
    BackgroundItem * b = (BackgroundItem*)in_b;
    offx1 += a->x_t;
    offy1 += a->y_t;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    offx2 += b->src_x;
    offy2 += b->src_y;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (a->flags & BOX_COLLISION) {
        int a_height = a_img->height;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    else if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        int a_height = a_img->height;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + a_yy * a_width + a_xx))[3] != 0))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + a_yy * a_width + a_xx))[3] != 0))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    else {
        int a_height = a_img->height;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!a_alpha.get(a_yy * a_width + a_xx))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!a_alpha.get(a_yy * a_width + a_xx))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool collide_tsprite_backdrop(CollisionBase * in_a, CollisionBase * in_b, int w, int h, int offx1, int offy1, int offx2, int offy2)
{
    SpriteCollision * a = (SpriteCollision*)in_a;
    BackdropCollision * b = (BackdropCollision*)in_b;
    offx1 += a->x_t;
    offy1 += a->y_t;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (a->flags & BOX_COLLISION) {
        int a_height = a_img->height;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    else if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        int a_height = a_img->height;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + a_yy * a_width + a_xx))[3] != 0))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + a_yy * a_width + a_xx))[3] != 0))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    else {
        int a_height = a_img->height;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!a_alpha.get(a_yy * a_width + a_xx))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int a_xxv = (x + offx1);
                    int a_yyv = (y + offy1);
                    int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                    int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                    if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                        continue;
                    if (!a_alpha.get(a_yy * a_width + a_xx))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool collide_tsprite_box(CollisionBase * in_a, int w, int h, int offx1, int offy1)
{
    SpriteCollision * a = (SpriteCollision*)in_a;
    offx1 += a->x_t;
    offy1 += a->y_t;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    if (a->flags & BOX_COLLISION) {
        int a_height = a_img->height;
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                int a_xxv = (x + offx1);
                int a_yyv = (y + offy1);
                int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                    continue;
                return true;
            }
        }
    }
    else if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        int a_height = a_img->height;
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                int a_xxv = (x + offx1);
                int a_yyv = (y + offy1);
                int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                    continue;
                if (!(((unsigned char*)(a_arr + a_yy * a_width + a_xx))[3] != 0))
                    continue;
                return true;
            }
        }
    }
    else {
        int a_height = a_img->height;
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                int a_xxv = (x + offx1);
                int a_yyv = (y + offy1);
                int a_xx = GET_SCALER_RESULT(a_xxv * a->co_divx - a_yyv * a->si_divx);
                int a_yy = GET_SCALER_RESULT(a_yyv * a->co_divy + a_xxv * a->si_divy);
                if ((a_xx | a_yy) < 0 || a_xx >= a_width || a_yy >= a_height)
                    continue;
                if (!a_alpha.get(a_yy * a_width + a_xx))
                    continue;
                return true;
            }
        }
    }
    return false;
}

static bool collide_background_sprite(CollisionBase * in_a, CollisionBase * in_b, int w, int h, int offx1, int offy1, int offx2, int offy2)
{
    BackgroundItem * a = (BackgroundItem*)in_a;
    SpriteCollision * b = (SpriteCollision*)in_b;
    offx1 += a->src_x;
    offy1 += a->src_y;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    else {
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool collide_background_tsprite(CollisionBase * in_a, CollisionBase * in_b, int w, int h, int offx1, int offy1, int offx2, int offy2)
{
    BackgroundItem * a = (BackgroundItem*)in_a;
    SpriteCollision * b = (SpriteCollision*)in_b;
    offx1 += a->src_x;
    offy1 += a->src_y;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    offx2 += b->x_t;
    offy2 += b->y_t;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        if (b->flags & BOX_COLLISION) {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!(((unsigned char*)(b_arr + b_yy * b_width + b_xx))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!b_alpha.get(b_yy * b_width + b_xx))
                        continue;
                    return true;
                }
            }
        }
    }
    else {
        if (b->flags & BOX_COLLISION) {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    return true;
                }
            }
        }
        else if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!(((unsigned char*)(b_arr + b_yy * b_width + b_xx))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!b_alpha.get(b_yy * b_width + b_xx))
                        continue;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool collide_background_background(CollisionBase * in_a, CollisionBase * in_b, int w, int h, int offx1, int offy1, int offx2, int offy2)
{
    BackgroundItem * a = (BackgroundItem*)in_a;
    BackgroundItem * b = (BackgroundItem*)in_b;
    offx1 += a->src_x;
    offy1 += a->src_y;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    offx2 += b->src_x;
    offy2 += b->src_y;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    else {
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool collide_background_backdrop(CollisionBase * in_a, CollisionBase * in_b, int w, int h, int offx1, int offy1, int offx2, int offy2)
{
    BackgroundItem * a = (BackgroundItem*)in_a;
    BackdropCollision * b = (BackdropCollision*)in_b;
    offx1 += a->src_x;
    offy1 += a->src_y;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    else {
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool collide_background_box(CollisionBase * in_a, int w, int h, int offx1, int offy1)
{
    BackgroundItem * a = (BackgroundItem*)in_a;
    offx1 += a->src_x;
    offy1 += a->src_y;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                    continue;
                return true;
            }
        }
    }
    else {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                    continue;
                return true;
            }
        }
    }
    return false;
}

static bool collide_backdrop_sprite(CollisionBase * in_a, CollisionBase * in_b, int w, int h, int offx1, int offy1, int offx2, int offy2)
{
    BackdropCollision * a = (BackdropCollision*)in_a;
    SpriteCollision * b = (SpriteCollision*)in_b;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    else {
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool collide_backdrop_tsprite(CollisionBase * in_a, CollisionBase * in_b, int w, int h, int offx1, int offy1, int offx2, int offy2)
{
    BackdropCollision * a = (BackdropCollision*)in_a;
    SpriteCollision * b = (SpriteCollision*)in_b;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    offx2 += b->x_t;
    offy2 += b->y_t;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        if (b->flags & BOX_COLLISION) {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!(((unsigned char*)(b_arr + b_yy * b_width + b_xx))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!b_alpha.get(b_yy * b_width + b_xx))
                        continue;
                    return true;
                }
            }
        }
    }
    else {
        if (b->flags & BOX_COLLISION) {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    return true;
                }
            }
        }
        else if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!(((unsigned char*)(b_arr + b_yy * b_width + b_xx))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            int b_height = b_img->height;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    int b_xxv = (x + offx2);
                    int b_yyv = (y + offy2);
                    int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                    int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                    if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                        continue;
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!b_alpha.get(b_yy * b_width + b_xx))
                        continue;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool collide_backdrop_background(CollisionBase * in_a, CollisionBase * in_b, int w, int h, int offx1, int offy1, int offx2, int offy2)
{
    BackdropCollision * a = (BackdropCollision*)in_a;
    BackgroundItem * b = (BackgroundItem*)in_b;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    offx2 += b->src_x;
    offy2 += b->src_y;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    else {
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool collide_backdrop_backdrop(CollisionBase * in_a, CollisionBase * in_b, int w, int h, int offx1, int offy1, int offx2, int offy2)
{
    BackdropCollision * a = (BackdropCollision*)in_a;
    BackdropCollision * b = (BackdropCollision*)in_b;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    else {
        if (b_alpha.data == NULL) {
            unsigned int * b_arr = (unsigned int*)b_img->image;
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                        continue;
                    return true;
                }
            }
        }
        else {
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                        continue;
                    if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                        continue;
                    return true;
                }
            }
        }
    }
    return false;
}

static bool collide_backdrop_box(CollisionBase * in_a, int w, int h, int offx1, int offy1)
{
    BackdropCollision * a = (BackdropCollision*)in_a;
    Image * a_img = a->image;
    BitArray & a_alpha = a_img->alpha;
    int a_width = a_img->width;
    if (a_alpha.data == NULL) {
        unsigned int * a_arr = (unsigned int*)a_img->image;
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (!(((unsigned char*)(a_arr + (y + offy1) * a_width + (x + offx1)))[3] != 0))
                    continue;
                return true;
            }
        }
    }
    else {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (!a_alpha.get((y + offy1) * a_width + (x + offx1)))
                    continue;
                return true;
            }
        }
    }
    return false;
}

static bool collide_box_sprite(CollisionBase * in_b, int w, int h, int offx2, int offy2)
{
    SpriteCollision * b = (SpriteCollision*)in_b;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (b_alpha.data == NULL) {
        unsigned int * b_arr = (unsigned int*)b_img->image;
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                    continue;
                return true;
            }
        }
    }
    else {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                    continue;
                return true;
            }
        }
    }
    return false;
}

static bool collide_box_tsprite(CollisionBase * in_b, int w, int h, int offx2, int offy2)
{
    SpriteCollision * b = (SpriteCollision*)in_b;
    offx2 += b->x_t;
    offy2 += b->y_t;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (b->flags & BOX_COLLISION) {
        int b_height = b_img->height;
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                int b_xxv = (x + offx2);
                int b_yyv = (y + offy2);
                int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                    continue;
                return true;
            }
        }
    }
    else if (b_alpha.data == NULL) {
        unsigned int * b_arr = (unsigned int*)b_img->image;
        int b_height = b_img->height;
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                int b_xxv = (x + offx2);
                int b_yyv = (y + offy2);
                int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                    continue;
                if (!(((unsigned char*)(b_arr + b_yy * b_width + b_xx))[3] != 0))
                    continue;
                return true;
            }
        }
    }
    else {
        int b_height = b_img->height;
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                int b_xxv = (x + offx2);
                int b_yyv = (y + offy2);
                int b_xx = GET_SCALER_RESULT(b_xxv * b->co_divx - b_yyv * b->si_divx);
                int b_yy = GET_SCALER_RESULT(b_yyv * b->co_divy + b_xxv * b->si_divy);
                if ((b_xx | b_yy) < 0 || b_xx >= b_width || b_yy >= b_height)
                    continue;
                if (!b_alpha.get(b_yy * b_width + b_xx))
                    continue;
                return true;
            }
        }
    }
    return false;
}

static bool collide_box_background(CollisionBase * in_b, int w, int h, int offx2, int offy2)
{
    BackgroundItem * b = (BackgroundItem*)in_b;
    offx2 += b->src_x;
    offy2 += b->src_y;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (b_alpha.data == NULL) {
        unsigned int * b_arr = (unsigned int*)b_img->image;
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                    continue;
                return true;
            }
        }
    }
    else {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                    continue;
                return true;
            }
        }
    }
    return false;
}

static bool collide_box_backdrop(CollisionBase * in_b, int w, int h, int offx2, int offy2)
{
    BackdropCollision * b = (BackdropCollision*)in_b;
    Image * b_img = b->image;
    BitArray & b_alpha = b_img->alpha;
    int b_width = b_img->width;
    if (b_alpha.data == NULL) {
        unsigned int * b_arr = (unsigned int*)b_img->image;
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (!(((unsigned char*)(b_arr + (y + offy2) * b_width + (x + offx2)))[3] != 0))
                    continue;
                return true;
            }
        }
    }
    else {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (!b_alpha.get((y + offy2) * b_width + (x + offx2)))
                    continue;
                return true;
            }
        }
    }
    return false;
}

static bool collide_box_box(int w, int h)
{
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            return true;
        }
    }
    return false;
}

