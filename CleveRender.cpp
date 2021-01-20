// CleveRender.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define print(x) std::cout << x


#include "./engine/graphic_engine.h"



int main()
{
    /*
    * W : front
    * S : back
    * A : left
    * D : right
    * E : up
    * Q : down
    * ¡ü : turn up
    * ¡ý : turn down
    * ¡û : turn left
    * ¡ú : turn right
    * 
    * e.g.
    *   //Show your model
    *   GraphicEngine demo;
    *   demo.loadObj("./obj/rock.obj"); //default "./obj/body.obj"
        if (demo.ConstructConsole(256, 240, 4, 4))
        {
            demo.Start();
        }
    *   ----------------------------------------
    *   //Show colored box
    *   GraphicEngine demo;
    *   demo.showBox(true);
        if (demo.ConstructConsole(256, 240, 4, 4))
        {
            demo.Start();
        }
        -----------------------------------------
        //Show Triangle Line
    *   GraphicEngine demo;
    *   demo.showLine(ture);
        if (demo.ConstructConsole(256, 240, 4, 4))
        {
            demo.Start();
        }
    */

    

    // Just Run
    GraphicEngine demo;
    if (demo.ConstructConsole(256, 240, 4, 4))
    {
        demo.Start();
    }

    

    return 0;
}

