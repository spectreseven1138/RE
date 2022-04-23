#ifndef INCLUDED_DRAW
#define INCLUDED_DRAW

#include "common/vector2.h"
#include "common/vector3.h"
#include "common/colour.h"
#include "node/types/camera_2d.h"

#include <string>
#include <functional>
using namespace std;

// Forward declarations
class Camera2D;

namespace Draw {

    void beginDrawing();
    void endDrawing();

    void loadStep(string message, bool reverse = false);

    template<typename... Arguments>
    void drawOnLayer(int layer, bool one_shot, void (*method)(Arguments...), Arguments... arguments) {
        Engine::getSingleton()->getTree()->addDrawFunction(layer, one_shot, (function<void(Arguments...)>)method, arguments...);
    }

    // - 2D draw methods -

    void drawLine(float start_x, float start_y, float end_x, float end_y, Colour colour, bool screen_position = false);
    void drawLine(Vector2 start, Vector2 end, Colour colour, bool screen_position = false);

    void drawTexture(TEXTURE_TYPE texture, Vector2 position, bool screen_position = false);
    void drawTextureRST(TEXTURE_TYPE texture, Vector2 position, float rotation, Vector2 scale, Colour tint, bool screen_position = false);

    void drawText(string text, float pos_x, float pos_y, Colour colour, float size = 1.0f, bool screen_position = true);
    void drawText(string text, Vector2 position, Colour colour, float size = 1.0f, bool screen_position = true);

    // - 3D draw methods -

    void drawCube(Vector3 position, Vector3 size, Colour colour = Colour::WHITE());
    void drawCube(Vector3 position, Vector3 size, TEXTURE_TYPE texture, Colour colour = Colour::WHITE());

    void drawGrid(int slices, float spacing);

}

#endif