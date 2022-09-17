#include <SDL2/SDL_image.h>
#include "TextureManager.h"
#include "../XmlParser/tinyxml.h"
#include "GameManager.h"
#include "../Controls/Vector2D.h"

TextureManager* TextureManager::_instance = nullptr;

void TextureManager::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;

    for (it = _texture.begin(); it != _texture.end(); ++it)
    {
        SDL_DestroyTexture(it->second);
    }
    
    _texture.clear();
}

bool TextureManager::ParseTextures(std::string source)
{
    TiXmlDocument xml;

    xml.LoadFile(source);

    if (xml.Error())
    {
        SDL_Log("Failed to loaded\n");
        return 0;
    }

    TiXmlElement* root = xml.RootElement();

    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("texture"))
        {
            std::string id = e->Attribute("id");
            std::string src = e->Attribute("source");
            Load(id, src);
        }
    }

    return 1;
}
bool TextureManager::Load(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());

    if (surface == 0)
    {
        SDL_Log("Failed to load surface: %s. Way texture: %s", SDL_GetError(), filename.c_str());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(GameManager::GetInstance()->GetRenderer(), surface);

    if (texture == 0)
    {
        SDL_Log("Failed to load texture: %s. Way texture: %s", SDL_GetError(), filename.c_str());
        return false;
    }

    _texture[id] = texture;
    return true;
}
void TextureManager::Draw(std::string id, int x, int y, int w, int h, float scaleX, float scaleY, float scroll, SDL_RendererFlip flip)
{
    SDL_Rect source = { 0, 0, w, h };
    SDL_Rect dest = { int(x), int(y), int(w), int(h) };


    SDL_RenderCopyEx(GameManager::GetInstance()->GetRenderer(), _texture[id], &source, &dest, 0, nullptr, flip);
}
void TextureManager::DrawFrame(std::string id, int x, int y, int w, int h, int r, int f, SDL_RendererFlip flip)
{
    SDL_Rect source = { w * f, h * r, w, h };
    SDL_Rect dest = { int(x), int(y), w, h };
    SDL_RenderCopyEx(GameManager::GetInstance()->GetRenderer(), _texture[id], &source, &dest, 0, nullptr, flip);
}
void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(_texture[id]);
    _texture.erase(id);
}

void TextureManager::DrawTile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect source = { tilesize * frame, tilesize *row, tilesize, tilesize };
    SDL_Rect dest = { int(x), int(y), tilesize, tilesize };

    SDL_RenderCopyEx(GameManager::GetInstance()->GetRenderer(), _texture[tilesetID], &source, &dest, 0, 0, flip);

}