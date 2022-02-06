#include "GraphicsManager.h"
#include <string>

GraphicsManager GraphicsManager::sGraphicsManager;

bool GraphicsManager::LoadTexture(int texid, const std::string& path) {
    if (textures[texid] != nullptr)
        SDL_DestroyTexture(textures[texid]);

    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if (loadedSurface == nullptr) {
        fprintf(stderr, "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return false;
    }

    if (renderer == nullptr) {
        fprintf(stderr, "Unable to create texture! Renderer is null.\n");
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
    if (newTexture == nullptr) {
        fprintf(stderr,  "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        SDL_FreeSurface(loadedSurface);
        return false;
    }

    SDL_FreeSurface( loadedSurface );
    textures[texid] = newTexture;
    return true;
}

void GraphicsManager::CreateTextureFromSurface(SDL_Surface* bg, TextureType texid) {
    if (!bg) {
        fprintf(stderr, "CreateTextureFromSurface called with empty argument.\n");
        return;
    }

    SDL_Surface* optimizedSurface = nullptr;
    SDL_Texture* newTexture = nullptr;

    Uint32 u_format = SDL_GetWindowPixelFormat(window);
    SDL_PixelFormat* format = SDL_AllocFormat(u_format);

    optimizedSurface = SDL_ConvertSurface(bg, format, 0 );

    SDL_FreeFormat(format);
    SDL_FreeSurface(bg);

    if (optimizedSurface == nullptr) {
        fprintf(stderr, "Unable to optimize background! SDL Error: %s\n", SDL_GetError());
        return;
    }

    newTexture = SDL_CreateTextureFromSurface( renderer, optimizedSurface );
    if (newTexture == nullptr) {
        fprintf( stderr, "Unable to create texture for bg! SDL Error: %s\n", SDL_GetError() );
    }

    SDL_FreeSurface( optimizedSurface );

    if (textures[texid] != nullptr) {
        SDL_DestroyTexture(textures[texid]);
    }
    textures[texid] = newTexture;
}

void GraphicsManager::DrawBeatmapBackground() {
    if (textures[TX_CURRENT_BG] != nullptr) {
        if (SDL_RenderCopy(renderer, textures[TX_CURRENT_BG], nullptr, nullptr) < 0) {
            fprintf(stderr, "DrawBeatmapBackground failed with: %s\n", SDL_GetError());
        }
    }
}

void GraphicsManager::Clear() {
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);
}

void GraphicsManager::Present() {
    SDL_RenderPresent(renderer);
}

void GraphicsManager::LoadTexturesForMode(ModeType mod) {
    switch (mod) {
        case MODE_PLAYER:
            LoadTexture(TX_PLAY_CIRCLE, "data/textures/circle.png");
            LoadTexture(TX_PLAY_CIRCLEOVERLAY, "data/textures/circleoverlay.png");
            LoadTexture(TX_PLAY_CIRCLEAPPROACH, "data/textures/circleapproach.png");

            LoadTexture(TX_PLAY_DISC, "data/textures/disc.png");
            LoadTexture(TX_PLAY_SLIDERTICK, "data/textures/slidertick.png");
            LoadTexture(TX_PLAY_SLIDERREVERSE, "data/textures/sliderreverse.png");

            LoadTexture(TX_WHITE, "data/textures/white.png");

            LoadTexture(TX_PLAY_SPINNER, "data/textures/spinner.png");
            LoadTexture(TX_PLAY_SPINNERBARS, "data/textures/spinnerbars.png");
            LoadTexture(TX_PLAY_SCOREBAR_BAR, "data/textures/scorebar_colour.png");

            LoadTexture(TX_PLAY_SPINNERBG, "data/textures/spinnerbg.png");

            LoadTexture(TX_PLAY_SLIDERB0, "data/textures/sliderb0.png");
            LoadTexture(TX_PLAY_SLIDERB1, "data/textures/sliderb1.png");
            LoadTexture(TX_PLAY_SLIDERB2, "data/textures/sliderb2.png");
            LoadTexture(TX_PLAY_SLIDERB3, "data/textures/sliderb3.png");
            LoadTexture(TX_PLAY_SLIDERB4, "data/textures/sliderb4.png");
            LoadTexture(TX_PLAY_SLIDERB5, "data/textures/sliderb5.png");
            LoadTexture(TX_PLAY_SLIDERB6, "data/textures/sliderb6.png");
            LoadTexture(TX_PLAY_SLIDERB7, "data/textures/sliderb7.png");
            LoadTexture(TX_PLAY_SLIDERB8, "data/textures/sliderb8.png");
            LoadTexture(TX_PLAY_SLIDERB9, "data/textures/sliderb9.png");
            LoadTexture(TX_PLAY_SLIDERFOLLOW, "data/textures/sliderfollow.png");

            LoadTexture(TX_PLAY_HIT0, "data/textures/hit0.png");
            LoadTexture(TX_PLAY_HIT300, "data/textures/hit300.png");
            LoadTexture(TX_PLAY_HIT300K, "data/textures/hit300k.png");
            LoadTexture(TX_PLAY_HIT300G, "data/textures/hit300g.png");

            LoadTexture(TX_PLAY_HIT50, "data/textures/hit50.png");
            LoadTexture(TX_PLAY_HIT100, "data/textures/hit100.png");
            LoadTexture(TX_PLAY_HIT100K, "data/textures/hit100k.png");

            LoadTexture(TX_PLAY_SLIDER30, "data/textures/slider30.png");
            LoadTexture(TX_PLAY_SLIDER10, "data/textures/slider10.png");

            LoadTexture(TX_PLAY_SCOREBAR_KI, "data/textures/scorebar_ki.png");
            LoadTexture(TX_PLAY_SCOREBAR_KIDANGER, "data/textures/scorebar_kidanger.png");
            LoadTexture(TX_PLAY_SCOREBAR_KIDANGER2, "data/textures/scorebar_kidanger2.png");

            LoadTexture(TX_PLAY_SCOREBAR, "data/textures/scorebar.png");
            break;
        case MODE_SONGSELECT:
            LoadTexture(TX_SONGSELECT_BG, "data/ui/song-selector.png");
            LoadTexture(TX_BUTTON_BIG, "data/ui/button-big.png");
            LoadTexture(TX_BUTTON_MED, "data/ui/button-med.png");
            LoadTexture(TX_BUTTON_SM, "data/ui/button-sm.png");
            break;
        case MODE_WELCOME:
            LoadTexture(TX_WELCOME_BG, "data/ui/welcome.png");
            LoadTexture(TX_TAP_TO_START, "data/ui/tap-to-start.png");
            break;
    }
}

void GraphicsManager::UnloadTexturesForMode(ModeType mod) {
    switch (mod) {
        case MODE_PLAYER:
            SDL_DestroyTexture(textures[TX_PLAY_CIRCLE]);
            SDL_DestroyTexture(textures[TX_PLAY_CIRCLEOVERLAY]);
            SDL_DestroyTexture(textures[TX_PLAY_CIRCLEAPPROACH]);

            SDL_DestroyTexture(textures[TX_PLAY_DISC]);
            SDL_DestroyTexture(textures[TX_PLAY_SLIDERTICK]);
            SDL_DestroyTexture(textures[TX_PLAY_SLIDERREVERSE]);

            SDL_DestroyTexture(textures[TX_WHITE]);

            SDL_DestroyTexture(textures[TX_PLAY_SPINNER]);
            SDL_DestroyTexture(textures[TX_PLAY_SPINNERBARS]);
            SDL_DestroyTexture(textures[TX_PLAY_SCOREBAR_BAR]);

            SDL_DestroyTexture(textures[TX_PLAY_SPINNERBG]);

            SDL_DestroyTexture(textures[TX_PLAY_SLIDERB0]);
            SDL_DestroyTexture(textures[TX_PLAY_SLIDERB1]);
            SDL_DestroyTexture(textures[TX_PLAY_SLIDERB2]);
            SDL_DestroyTexture(textures[TX_PLAY_SLIDERB3]);
            SDL_DestroyTexture(textures[TX_PLAY_SLIDERB4]);
            SDL_DestroyTexture(textures[TX_PLAY_SLIDERB5]);
            SDL_DestroyTexture(textures[TX_PLAY_SLIDERB6]);
            SDL_DestroyTexture(textures[TX_PLAY_SLIDERB7]);
            SDL_DestroyTexture(textures[TX_PLAY_SLIDERB8]);
            SDL_DestroyTexture(textures[TX_PLAY_SLIDERB9]);
            SDL_DestroyTexture(textures[TX_PLAY_SLIDERFOLLOW]);

            SDL_DestroyTexture(textures[TX_PLAY_HIT0]);
            SDL_DestroyTexture(textures[TX_PLAY_HIT300]);
            SDL_DestroyTexture(textures[TX_PLAY_HIT300K]);
            SDL_DestroyTexture(textures[TX_PLAY_HIT300G]);

            SDL_DestroyTexture(textures[TX_PLAY_HIT50]);
            SDL_DestroyTexture(textures[TX_PLAY_HIT100]);
            SDL_DestroyTexture(textures[TX_PLAY_HIT100K]);

            SDL_DestroyTexture(textures[TX_PLAY_SLIDER30]);
            SDL_DestroyTexture(textures[TX_PLAY_SLIDER10]);

            SDL_DestroyTexture(textures[TX_PLAY_SCOREBAR_KI]);
            SDL_DestroyTexture(textures[TX_PLAY_SCOREBAR_KIDANGER]);
            SDL_DestroyTexture(textures[TX_PLAY_SCOREBAR_KIDANGER2]);

            SDL_DestroyTexture(textures[TX_PLAY_SCOREBAR]);
            break;
        case MODE_SONGSELECT:
            SDL_DestroyTexture(textures[TX_SONGSELECT_BG]);
            SDL_DestroyTexture(textures[TX_BUTTON_BIG]);
            SDL_DestroyTexture(textures[TX_BUTTON_MED]);
            SDL_DestroyTexture(textures[TX_BUTTON_SM]);
            break;
        case MODE_WELCOME:
            SDL_DestroyTexture(textures[TX_WELCOME_BG]);
            SDL_DestroyTexture(textures[TX_TAP_TO_START]);
            break;
    }
}

void GraphicsManager::Draw(TextureType tex, int32_t x, int32_t y, uint32_t width, uint32_t height, DrawOrigin origin, FieldType fieldtype, SDL_Color color, uint32_t alpha, int32_t angle, float z, const SDL_Rect* uv)
{
    int32_t x1 = SCREEN_WIDTH, x2 = (SCREEN_WIDTH+100), y1 = SCREEN_HEIGHT, y2 = (SCREEN_HEIGHT+100);
    //float z = zvalue[tex] + deltaz;

    if (uv != nullptr) {
        width = uv->w;
        height = uv->h;
    }

    if (fieldtype == FIELD_PLAY)
    {
        x += PlayXOffset;
        y += PlayYOffset;
    }

    switch (origin)
    {
        case ORIGIN_TOPLEFT:
            x1 = ForceBounds(x);
            x2 = ForceBounds(x + width);
            y1 = ForceBounds(y);
            y2 = ForceBounds(y + height);
            break;

        case ORIGIN_CENTER:
            width /= 2;
            height /= 2;

            x1 = ForceBounds(x - width);
            x2 = ForceBounds(x + width);
            y1 = ForceBounds(y - height);
            y2 = ForceBounds(y + height);
            break;

        case ORIGIN_BOTTOMLEFT:
            x1 = ForceBounds(x);
            x2 = ForceBounds(x + width);
            y1 = ForceBounds(y - height);
            y2 = ForceBounds(y);
            break;

        case ORIGIN_TOPRIGHT:
            x1 = ForceBounds(x - width);
            x2 = ForceBounds(x);
            y1 = ForceBounds(y);
            y2 = ForceBounds(y + height);
    }

    //don't draw things out of the screen
    if (x1 > SCREEN_WIDTH || x2 < 0 || y1 > SCREEN_HEIGHT || y2 < 0)
        return;
    SDL_Rect dst = {x1, y1, x2-x1, y2-y1};

    SDL_SetTextureAlphaMod(textures[tex], alpha);

    SDL_RenderCopyEx( renderer, textures[tex], uv, &dst, angle, nullptr, SDL_FLIP_NONE );
}

int32_t GraphicsManager::ForceBounds(int32_t value)
{
    if (value < -200)
        return -200;

    if (value > 1099)
        return 1099;

    return value;
}

//TODO: Move to sprites
void GraphicsManager::DrawFullScreenRectangle(SDL_Color c)
{
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_Rect r = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &r);
}
