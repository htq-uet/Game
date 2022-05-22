# ---KIT AND KAT--- <br />
## -Introduction: <br />
A Co-op game project of 3 individuals : Hoang Thai Quang(Leader), Tran Thi Van Anh, Nguyen Le Linh Chi <br />
In this game, you have to take control two cats name Kit(the pink one) and Kat(the black one) to eat all of fish and get to the gate. The end gate will bring to the winning. Be careful about some colorful liquid. <br />

## -MAKEFILE

+All:
	g++ -w -ISDL2\include -LSDL2\lib -o KitandKat src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

## -Devision of work: <br />
Create the main function of project, find assets, improve and add some small functions(Base Function, Text, Sound, FPS,..) : Together. <br />
Guide other members, add Players, Maps and MapTiles, makefile : Hoang Thai Quang. <br />
Add Collision, Savegame, Continuos button : Tran Thi Van Anh. <br />
Design, add Game States(include GameOver, Winning, Menu, Tutorial), add score counter  : Nguyen Le Linh Chi. <br />
Other Objects(Gate, Mushroom) : Chi + Van Anh. <br />
