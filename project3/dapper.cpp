#include "raylib.h"

int main()
    {

    int wheight, wwidth;
    wheight = 380;
    wwidth = 512;
    InitWindow(wwidth, wheight, "dapidabudab");
    SetTargetFPS(60);
    
    int velocity = 0;
    // zmiana (pixel/s)/s pixel przez czas
    const int gravity = 1'000;       

    //scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");                           //wczytanie tekstury
    Rectangle scarfyRec; 
    scarfyRec.width = scarfy.width/6;                                                  // dzielimy przez szesc po zdjecie jest polaczone z 6 animacji postaci
    scarfyRec.height = scarfy.height;   
    scarfyRec.x = 0;
    scarfyRec.y = 0;                                                                // ustawienie postaci jako kwadrat
    Vector2 scarfyPos;  
    scarfyPos.x = wwidth/2 - scarfyRec.width/2;   
    scarfyPos.y = wheight - scarfyRec.height;                                      // ustalenie pozycji przez specjalną funckję vector2

    //nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
    Rectangle nebRec;
    nebRec.width = nebula.width/8;
    nebRec.height = nebula.height/8;
    nebRec.x = 0;
    nebRec.y = 0;
    Vector2 nebPos;
    nebPos.x = wwidth;
    nebPos.y = wheight-nebRec.height;




    //czy jest w powietrzu
    bool isInAir;
    //predkosc skoku pixel/sekunde
    const int jumpVel = -600;
    // predkosc nebuli
    const int nebulaVel = -400;
  // klatka animacji dla scarfy
  int frame;
   const float updateTime = 1.0/12.0;                           // czas zmiany klatki muszą być te kropki bo wtedy liczy czas
   float runningTime = 0;

// klatki animacji dla nebuli
  int nebFrame;
  const float nebUpdateTime = 1.0/12.0;
   float nebRunningTime = 0;
    
    while (WindowShouldClose() == false)                                             // (!WindowShouldClose())
        {

          //delta time czas od ostatniej klatki
            const float dT{GetFrameTime()};
            

        BeginDrawing();
        ClearBackground(WHITE);
    

        // obiekt na ziemii
        if (scarfyPos.y >= wheight - scarfyRec.height )   
        {
            velocity =0;
             isInAir = false;
             

        }
        //obiekt w powietrzu
        else
        {
            velocity += gravity * dT;
            isInAir = true;
             runningTime = 0;
        }

         if (IsKeyPressed(KEY_SPACE) && isInAir ==false)
      { 
        
         velocity +=jumpVel;      // przez minus nasz obiekt idzie do góry 
      }
       if (IsKeyPressed(KEY_D))
      { 
        
         scarfyPos.x += 10;       // przez minus nasz obiekt idzie do góry 
      }

        // update pozycji nebul
        nebPos.x +=nebulaVel *dT;
        // update pozycji scarfy
       scarfyPos.y += velocity * dT;

      // update biegu żeby klatki sie zmienialy
        runningTime +=dT;





      // animacja scarfy
      if(runningTime >=updateTime)
      {
        runningTime = 0.0;
        // aktualizacja klatki animacji
        scarfyRec.x=frame*scarfyRec.width;
       frame++;
       if(frame > 5)
       {
        frame = 0;
       }
      }


      //animacja nebuli
      if(runningTime >=updateTime)
      {
        runningTime = 0.0;
        // aktualizacja klatki animacji
        nebRec.x=frame*nebRec.width;
       frame++;
       if(frame > 7)
       {
        frame = 0;
       }
      }
   



        DrawTextureRec(scarfy, scarfyRec, scarfyPos, WHITE);
        DrawTextureRec(nebula, nebRec,nebPos,WHITE);

        // rysowanie postaci

        EndDrawing();

        }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();

    }