# SFML_snake
This SFML snake is the course project for "Object Oriented Programming",
ans is based on source code from "https://github.com/jhpy1024/sfSnake"

How to play

1.	Run main.exe (make sure you have sfml2.5 set correctly in your computer & mingw64 for the match version) and follow the instructions to set up your own theme before you start the journey.
	You are allowed to choose different types of background colors and grids in this page.

2.	Use ↑ ↓ ← → to move your snake towards different directions or simply click your mouse
	inside game screen which makes the
	snake turn to that direction.

3.	When your snake successfully eat the fruit on the screen, it may grow;

		Black / Brown fruits 	---- 	grow 0 node
		Green fruits 		---- 	grow 1 node
		Blue fruits		---- 	grow 2 nodes
		Red fruits 		---- 	grow 3 nodes

4.	There are also gems(one at a time) and bombs(two at a time) in the game, you can see them as bonus fruits.
	Every time you eat a normal fruit, those three bonus fruits' position will change so that it would be a bit
	hard to eat them. Each time your snake manage to eat a gem, the snake earns 15 nodes length as bonus! But be
	careful to keep away from the bomb which makes you lose the game immediately.
	
5.	Every time you lose the game, you can see the total score you got on the screen.(We offer you 5 scores originally)





2020-06-08 添加了课程设计提交的代码说明

源代码在PJ_Snake_with_SFML文件夹中，其中添加了Textures文件夹用于存放程序中所有texture调用的png图片，均通过PhotoShop进行绘制并调整到合适的图像大小以适应程序。

实现功能：

1、通过鼠标控制蛇的移动，每次点击鼠标，蛇会朝鼠标点击方向移动。同时调整了边缘碰撞的检测函数，修正了蛇无法检测边缘碰撞的问题。

2、修改了fruit部分对应的代码，修正了水果只生成在特定行上的问题。同时加入

		enum class color
		{
			Black, Brown, Red, Blue, Green, GEM, BOMB
		};

对于不同颜色的水果进行了区分。前五种水果和pdf要求上一致，黑色褐色水果不增加长度，绿色+1，蓝色+2，红色+3.后两种是额外实现的功能，将在后面进一步解释说明。

3、对贪吃蛇、水果以及背景色、网格等图案采用sprite+texture进行绘制，图片存放于Textures文件夹中。

4、修改了MenuScreen.cpp中的相应函数，在GameScreen开始前增设了两级用户设置菜单。通过检测用户的键盘输入来选择不同的背景图色（黑白褐色）和网格类型（黑白褐色/无网格）。其中由于白色网格绘制后过于刺眼不适宜长时间游玩，采用靛青色网格进行替代。运行程序的时候，先绘制背景图，在绘制网格（如果有的话）最后绘制水果和蛇来保证图形界面的正常显示。

5、参考pdf要求中给出的效果图对程序进行了进一步改进。效果图中蛇头和蛇身、蛇身和蛇身结点之间发生了重合，和原有检查自碰撞的函数并不兼容。由于在完成大作业的过程中先实现了街机画风下的所有要求的功能，并且考虑到蛇身部分本身要求使用圆形叠加矩形进行绘制，在蛇头和蛇身部分采用两层sprite，两层sprite同时移动，引入

		std::pair<sf::Sprite, sf::Sprite> BodyNode_;

替代原有的长方形shape来存放两层sprite。蛇身部分，黄色圆形作为底座，只负责移动不参与碰撞检测和旋转，黑色矩形部分参与方向改变时的旋转和碰撞的检测。蛇头部分，引入一个尽量小（记得是6像素*6像素矩形背景）的黑色矩形作为底座，绘制了稍大一些的扁长方形背景的蛇头（因为没找到pdf上的原图，便参考pdf上的图片进行了绘制，可能略有出入）。这里小圆形底座负责碰撞检测的部分，这样能够在鼠标控制转弯的时候获得尽可能更大的转角。同时通过调整蛇身结点之间的距离以及蛇头底座的大小保证碰撞检测函数的正确性和可行性。

6、为了提高游戏的可玩性，增设了GEM和BOMB两种水果种类并且绘制了紫色宝石和炸弹的png图片。在原定的每次显示12个水果，其中25%是黑/褐色（pdf要求）以外，增加了一枚宝石和两枚炸弹。贪吃蛇吃到宝石可以增加15点长度，但吃到炸弹则会导致游戏结束（引入了新的函数判断是否吃到炸弹，并且根据此在update中加入了新的check函数来更新screen状态）（宝石和两枚炸弹恒定存放于fruit_的前三位，宝石每次只出现一个，被吃掉后通过设定新的位置来重新出现。由于炸弹会导致游戏失败，所以现有框架下fruit_的前三个元素是不需要通过更新水果来进行修改的）

7、相应游戏平衡性的调整：由于宝石的图片比水果较大些，更容易吃到且回报较高，为了保证平衡性，将加大宝石获取难度以及炸弹引爆可能性。修改检查水果碰撞函数，每当玩家吃掉了一个水果，就重新设定宝石和炸弹的位置。炸弹可能会突然出现在蛇的前方，宝石的位置也在不断变化，通过这种方式来平衡宝石收益过高的问题。

8、修改了游戏BGM，由于原BGM过于难听，选取“冰淇凌爱情”作为游戏背景音乐。（这就有80年代很古早的感觉了）由于未找到合适的素材作为pickup sound，未设置拾取音效。

变量的生存期：

由于蛇、水果、网格和背景都是始终贯穿游戏过程的，故生存期与GameScreen的生存期相同。

编译环境说明：

采用vscode进行编译。源代码中已经包括makefile和.vscode文件夹。在vscode中打开文件夹并且在终端运行mingw32-make指令即可自动生成main.exe文件。双击运行即可。（需要把sfml2.5\lib添加到环境变量中）
