#include "displaygl.h"
#include <cmath>
#include <QtOpenGL>
#include <QtGui>
#include <QBrush>
#include <QtCore>
#include <QRect>
#include <QPainter>
#include <QPaintEvent>

#include <QDebug>
#include <iostream>
#include <QPixmap>
#include <QString>
#include "adjacency.h"
#include "roomlist.h"

#define MAX_LEVELS 2

using namespace std;

displayGL::displayGL(QString serverID, int serverPort, QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

    Evil =  new NetworkOfAlignment(serverID,serverPort); // SET UP THE NETWORK CONNECTION FOR THE CLIENT

    connect(Evil, SIGNAL(LocationsChanged(QStringList)), this, SLOT(ChangeLocations(QStringList)));
    connect(Evil, SIGNAL(GameOver(QString)), this, SLOT(myGameOver(QString)));
    connect(Evil, SIGNAL(gotDamage(int)), &thePlayer, SLOT(TakeDamage(int))); // if it's us (chked already) we take the damage
    connect(Evil, SIGNAL(serverSocket(int)), this, SLOT(getServerSocket(int)));
    connect(&thePlayer, SIGNAL(rebirth()), this, SLOT(bornagain()));
    setAutoFillBackground(false);
    current_direction = WEST;
    start_loc = new int[10];
    start_loc[0]=9;
    start_loc[1]=17;
    start_loc[2]=22;
    current_level = 0;
    current_room = start_loc[0];
    for (int i = 0; i < 5; i++)
    {
        MonsterPointers[i] = new monster;
        connect(MonsterPointers[i], SIGNAL(DamagePlayer(int)), &thePlayer, SLOT(TakeDamage(int)));
    }
    init_fp();
    show_map = false;
}

displayGL::~displayGL()
{

}

void displayGL::init_fp()
{
    for(uint i = 0; i < 128; i++)
        key_fptrs[i] = &displayGL::doNothing;
    key_fptrs[Qt::Key_W] = key_fptrs[Qt::Key_8] = &displayGL::moveForward;
    key_fptrs[Qt::Key_S] = key_fptrs[Qt::Key_2] = &displayGL::moveBackward;
    key_fptrs[Qt::Key_A] = key_fptrs[Qt::Key_4] = &displayGL::turnLeft;
    key_fptrs[Qt::Key_D] = key_fptrs[Qt::Key_6] = &displayGL::turnRight;
    key_fptrs[Qt::Key_M] = key_fptrs[Qt::Key_5] = &displayGL::showminimap;
    key_fptrs[Qt::Key_Space] = &displayGL::attack;
    key_fptrs[Qt::Key_O] = &displayGL::PickUpItem;
    key_fptrs[Qt::Key_P] = &displayGL::DropItem;
}

void displayGL::loadTextures()
{
    m_images[0] = convertToGLFormat(QImage("BackWall.png", "PNG"));
    m_images[1] = convertToGLFormat(QImage("Wall.png", "PNG"));
    m_images[2] = convertToGLFormat(QImage("LockedDoor1.png", "PNG"));
    m_images[3] = convertToGLFormat(QImage("LockedDoor2.png", "PNG"));
    m_images[4] = convertToGLFormat(QImage("LockedDoor3.png", "PNG"));
    m_images[5] = convertToGLFormat(QImage("LockedDoor4.png", "PNG"));
    glEnable(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(40, texture_ids);
    for (uint i = 0 ; i < 6; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture_ids[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_images[i].width(), m_images[i].width(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_images[i].bits());
    }
    // bind the images to the textures
}

void displayGL::initializeGL()
{
    glClearColor(0,0,0,0); // set clear color buffer bit
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    loadTextures();
}

void displayGL::paintEvent(QPaintEvent *event)
{
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    int count_ahead = 0; // forward
    int my_room = current_room;
    int i = 0;

    weights* forward = NULL;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QMutex thisMutex;
    vector< vector<int> > P_Loc_Sz; // possibly have to be vectors when you can select what number's bitpattern will display how you look!
    vector< vector<int> > M_Loc_Sz; // Monster # (from which you can get type), Depth
    do {
        my_room = my_room + count_ahead;
        switch(current_direction)
        {
        case NORTH:
            drawRoom(WEST, EAST, my_room, i, P_Loc_Sz, M_Loc_Sz);
            break;
        case SOUTH:
            drawRoom(EAST, WEST, my_room, i, P_Loc_Sz, M_Loc_Sz);
            break;
        case EAST:
            drawRoom(NORTH, SOUTH, my_room, i, P_Loc_Sz, M_Loc_Sz);
            break;
        default:
            drawRoom(SOUTH, NORTH, my_room, i, P_Loc_Sz, M_Loc_Sz);
            break;
        }
        count_ahead = countAhead(current_direction);
        forward = checkAhead(my_room, my_room+count_ahead);
        i++;
    } while (forward && i < 4 && !forward->isDoor()); // stops at a door, can't see through it
    forward && (drawBackWall(i, forward->isDoor(), current_level));
    !forward && (drawBackWall(i, 0, current_level));

    if (the_rooms.rooms[current_level][current_room]->getQuestions().size() > 0)
        drawQuestion(current_level, current_room, &painter);

    // DRAW PEOPLE AND MONSTERS AFTER BACK WALL (PNGs WITH TRANSPARENCY)
    (P_Loc_Sz.size() > 0) && ( drawEnemies(P_Loc_Sz, &painter) );
    (M_Loc_Sz.size() > 0) && ( drawMonsters(M_Loc_Sz, &painter) );


    showInfo(&painter); // show the info at the top of the screen
    showitems(&painter); // show available items in the room
    (show_map) && showminimap(&painter); // no ifs or buts, but one and
    (in_rm_inventory) && showthisitem(&painter);
    (in_inventory) && showmyitem(&painter);
    painter.end();
    update();
}

void displayGL::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspectiveGL(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// http://nehe.gamedev.net/article/replacement_for_gluperspective/21002/
// replacing GLU which is not present on Mac in standard OpenGL
void displayGL::perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;

    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

void displayGL::mousePressEvent(QMouseEvent *e)
{
    e->accept();
}

void displayGL::keyPressEvent(QKeyEvent *event)
{
    if (in_rm_inventory)
    {
        items* item_to_get;
        int num_items_here = the_rooms.rooms[current_level][current_room]->getItems().size();
        switch(event->key())
        {
        case Qt::Key_Left:
            ((item_at-1) >= 0) && item_at--;
            break;
        case Qt::Key_Right:
            ((item_at+1) < num_items_here) && item_at++;
            break;
        case Qt::Key_Return:
        case Qt::Key_Enter:
            (item_at >= 0 && item_at < num_items_here) &&
                    (item_to_get = the_rooms.rooms[current_level][current_room]->removeItem(item_at));
            thePlayer.addItem(item_to_get); /// Give the player the item
            glFlush();
            in_rm_inventory = false;
            checkifwon();
            break;
        case Qt::Key_Escape:
            in_rm_inventory = false;
            break;
        }
    }
    else if (in_question)
    {
            switch(event->key())
            {
            case Qt::Key_A:
                answerQuestion(0);
                in_question = false;
                break;
            case Qt::Key_B:
                (num_answers > 1) && answerQuestion(1);
                in_question = false;
                break;
            case Qt::Key_C:
                (num_answers > 2) && answerQuestion(2);
                in_question = false;
                break;
            case Qt::Key_D:
                (num_answers > 3) && answerQuestion(3);
                in_question = false;
                break;

            }
    }
    else if (in_inventory)
    {
        items* remitem;
        int num_items_here = thePlayer.getItems().size();
        switch(event->key())
        {
        case Qt::Key_Left:
            ((item_at-1) >= 0) && item_at--;
            break;
        case Qt::Key_Right:
            ((item_at+1) < num_items_here) && item_at++;
            break;
        case Qt::Key_Return:
        case Qt::Key_Enter:
            (item_at >= 0 && item_at < num_items_here) &&
                    (remitem = thePlayer.getItems()[item_at]);
            thePlayer.dropItem(remitem);
            the_rooms.rooms[current_level][current_room]->addItem(remitem);
            glFlush();
            in_inventory = false;
            break;
        case Qt::Key_Escape:
            in_inventory = false;
            break;
        }
    }
    else
        if (event->key() < 128 && event->key() >= 0)
            (this->*(key_fptrs[event->key()]))();
}

void displayGL::showInfo(QPainter *toPaint)
{
    QString Info = tr("Direction: ");

    if (current_direction == NORTH)
        Info.append(tr("NORTH"));
    else
        if (current_direction == SOUTH)
            Info.append(tr("SOUTH"));
        else
            if (current_direction == EAST)
                Info.append(tr("EAST"));
            else
                Info.append(tr("WEST"));
    Info.append( "     Room: ").append(QString::number(current_room));
    QFont font("times", 10);
    toPaint->setFont(font);
    QFontMetrics metrics = QFontMetrics(font); // from http://qt-project.org/doc/qt-4.8/opengl-overpainting.html
    int border = qMax(4, metrics.leading());
    QRect rect = metrics.boundingRect(0, 0, width() - 2*border, int(height()*0.125),
                                      Qt::AlignRight | Qt::TextSingleLine, Info);
    toPaint->setRenderHint(QPainter::Antialiasing);
    toPaint->setPen(Qt::white);
    toPaint->drawText((width()-rect.width())/2, border, rect.width(), rect.height(),Qt::AlignCenter|Qt::TextSingleLine, Info);
    update();
}

void displayGL::ChangeLocations(QStringList playerlocations)
{
    QMutex thisMutex;
    thisMutex.lock();
    PlayerLocations.clear();
    for (int i = 0; i < playerlocations.size(); i++)
    {
        QStringList player_loc = playerlocations[i].split("-");
        PlayerLocations.push_back(make_pair(player_loc[1].toInt(),player_loc[0].toInt())); // reverse and make a pair
    }
    thisMutex.unlock();
}

void displayGL::myGameOver(QString playerID)
{
    // Got signal that someone won....
    // Go to next level
    if (current_level < MAX_LEVELS)
    {
        current_level++;
        current_room = start_loc[current_level];
        current_direction = (DIRECTION)(rand()%4);
        thePlayer.hasItem(theItems.itemlist["orb_win"]) && thePlayer.dropItem(theItems.itemlist["orb_win"]);
    } else
    {
        // display out that the game is over
        // DISPLAY SCORES
        qDebug() << "WON!" <<endl;
    }

}

void displayGL::getServerSocket(int socket)
{
    myServerSocket = socket;
}

void displayGL::bornagain()
{
    thePlayer.resetstats();
    current_room = start_loc[current_level];
    current_direction = (DIRECTION)(rand()%4);
    thePlayer.hasItem(theItems.itemlist["orb_win"]) && thePlayer.dropItem(theItems.itemlist["orb_win"]);
    update();
    glFlush();
}

// Basically a draw a vertical trapezoid function
// Whatever calls it will give at what depth it needs to be drawn and what side of the wall it's on
bool displayGL::drawSideWall(bool left_right, weights* access, int start_depth, int level)
{
    double wallstops[6] = {2.0,1.5,1.1,.8,0.6,0}; // anything beyond 5 wall segments out it non-existent in view
    level = level;
    /*
     *  |\     |     /|
     *  | \    |    / |
     *  |  |_  |  /|  |
     *  |  | |-+-| |  |
     * -+--+-+-2-+1+-0+-
     *  |  |_|-+-| |  |
     *  |  |___|__\|  |   A Hallway with one corner to the left
     *  | /    |    \ |
     *  |/_____|_____\|
     *         |
     */

    double start_x;
    double end_x;
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    if (access) // if we are a weight... that is: if there is something on the other side of what we're displaying
    {
        glColor3f(.35,.35,.35);
        glBindTexture(GL_TEXTURE_2D, texture_ids[access->isDoor()]);
    }
    else // just a wall
    {
        glColor3f(.1,.1,.1);
        glBindTexture(GL_TEXTURE_2D, texture_ids[0]);
    }

    if ( !access || access->isDoor() )
    {
        // SIDE WALL(no weights) OR DOOR (isDoor > 0)
        start_x = wallstops[start_depth] * (left_right ? 1 : -1);
        end_x = wallstops[start_depth+1] * (left_right ? 1 : -1);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(start_x,-1.0,-1.*start_depth-1);
        glTexCoord2f(0.0, 1.0); glVertex3f(start_x, 1.0,-1.*start_depth-1);
        glTexCoord2f(1.0, 1.0); glVertex3f(end_x,   1.0,-1.*start_depth-2);
        glTexCoord2f(1.0, 0.0); glVertex3f(end_x,  -1.0,-1.*start_depth-2);
        glEnd();
        glFlush();
        glDisable(GL_TEXTURE_2D);
        return 1;
    }
    else
    {
        // DRAW A CORNER ( isDoor == 0 )
        end_x = (wallstops[start_depth+2] * (left_right ? 1 : -1));
        start_x = end_x + (wallstops[start_depth])*(left_right ? 1 : -1);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(start_x,-1.0,-1.*start_depth-2);
        glTexCoord2f(0.0, 1.0); glVertex3f(start_x, 1.0,-1.*start_depth-2);
        glTexCoord2f(1.0, 1.0); glVertex3f(end_x,   1.0,-1.*start_depth-2);
        glTexCoord2f(1.0, 0.0); glVertex3f(end_x,  -1.0,-1.*start_depth-2);
        glEnd();
        glFlush();
        glDisable(GL_TEXTURE_2D);
        return 1;

    }
}

bool displayGL::drawRoom(DIRECTION one, DIRECTION two, int my_room, int depth, vector<vector<int> > &P_Loc_Sz, vector<vector<int> > &M_Loc_Sz)
{
    drawSideWall(0,checkAhead(my_room,my_room+countAhead(one)), depth, current_level);
    drawSideWall(1,checkAhead(my_room,my_room+countAhead(two)), depth, current_level);
    QMutex thisMutex;
    thisMutex.lock();
    int sizepl = PlayerLocations.size();
    for (int k = 0; k < sizepl; k++)
    {
        if (PlayerLocations[k].first==my_room && PlayerLocations[k].second!=myServerSocket)
        {
            vector<int> player_in_room;
            player_in_room.push_back(my_room); // where they are
            player_in_room.push_back(PlayerLocations[k].second); // player's id
            player_in_room.push_back(depth); // depth away from me
            P_Loc_Sz.push_back(player_in_room);
        }
    }
    thisMutex.unlock();
    for (int k = 0; k < 5; k++)
    {
        if (MonsterPointers[k]->getRoom() == my_room)
        {
            vector<int> monster_in_room;
            monster_in_room.push_back(my_room);
            monster_in_room.push_back(MonsterPointers[k]->getType());
            monster_in_room.push_back(depth);
            M_Loc_Sz.push_back(monster_in_room);
        }
    }
}

// Precondition: side walls (trapezoids) are drawn and filled with texture?
// Postcondition: back wall is drawn at depth of end of walls that are visible
// Draws a rectangle at the center of the dispaly (dimensions depend on depth, color depends on direction??)
bool displayGL::drawBackWall(int depth, int type, int level)
{
    level=level;
    double wallstops[6] = {2.0,1.5,1.1,.8,0.6,0}; // anything beyond 5 wall segments out it non-existent in view
    if (depth > 4)
        return 0; // we can't draw a wall that far away, it's too dark to see

    double start_x = wallstops[depth];

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_ids[type]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-start_x,-1.0,(-1*depth)-1);
    glTexCoord2f(0.0, 1.0); glVertex3f(-start_x, 1.0,(-1*depth)-1);
    glTexCoord2f(1.0, 1.0); glVertex3f( start_x, 1.0,(-1*depth)-1);
    glTexCoord2f(1.0, 0.0); glVertex3f( start_x,-1.0,(-1*depth)-1);
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);
    return 1;
}


weights *displayGL::checkAhead(int room_number, int next_room)
{
    return adjacencyTable.getWeight(room_number, next_room, current_level);
}

int displayGL::countAhead(DIRECTION dir)
{
    return dir == NORTH? 1 : dir == WEST ? -8 : dir == SOUTH? -1 : 8;
}

void displayGL::moveForward()
{
    int count_ahead = countAhead(current_direction);
    if ((current_room + count_ahead) > 54 || (current_room + count_ahead) < 9)
        return; // Easy out first, less time to compute bad moves
    weights* testForward;
    if ( (testForward = checkAhead(current_room, current_room + count_ahead)) )
    {
        // This is where we test if we meet the weights requirement!!!!!!!!!!!!!!!!!!!
        //
        bool hasstats = checkstats(testForward);
        bool hasitems = checkitems(testForward);
        if (hasitems && hasstats)
        {
            current_room = current_room + count_ahead;
            Evil->moveToServer(current_room); // only send the move if we have the correct items and stats
            // move zombies after person successfully moves
            for (int i = 0; i < 5; i++)
            {
                MonsterPointers[i]->PlayerMoved(current_room);
                MonsterPointers[i]->MakeMove();
            }
        }
    }
    update();
    updateGL();
}

void displayGL::moveBackward()
{
    int count_ahead = -1 * countAhead(current_direction);
    if ((current_room + count_ahead) > 54 || (current_room + count_ahead) < 9)
        return; // Easy out first, less time to compute bad moves
    weights* testForward;
    if ( (testForward = checkAhead(current_room, current_room + count_ahead)) )
    {
        bool hasstats = checkstats(testForward);
        bool hasitems = checkitems(testForward);
        // This is where we test if we meet the weights requirement!!!!!!!!!!!!!!!!!!!
        //
        if (hasitems && hasstats)
        {
            current_room = current_room + count_ahead;
            Evil->moveToServer(current_room); // only send the move if we have the correct items and stats
        }
    }
    update();
    updateGL();
}


bool displayGL::checkstats(weights* testForward)
{
    bool hasstats= false;
    int thesize = testForward->getStats().size();
    if (thesize == 0)
        hasstats = true;
    for( int i = 0; i < thesize; i++)
    {
        if (testForward->getStats()[i].first.first == "")
            hasstats = true; // no stats required
        else
            hasstats = (thePlayer.hasStat(testForward->getStats()[i].first.first, testForward->getStats()[i].first.second)) ? true : false;

        if (hasstats == true  && testForward->getStats()[i].second.first == "")
            hasstats = true; // no stats required
        else
            if ( hasstats == true ) // must already be true or false
                hasstats = (thePlayer.hasStat(testForward->getStats()[i].second.first, testForward->getStats()[i].second.second)) ? true : false;
        // not adequate stats
    }
    return hasstats;
}


bool displayGL::checkitems(weights* testForward)
{
    bool hasitems = false;
    int thesize = testForward->getItems().size();
    if (thesize == 0)
        return true; // no items to test
    for( int i = 0; i < thesize; i++)
        if (!thePlayer.hasItem(testForward->getItems()[i]))
            return false; // does not have a required item
    return true;
}

void displayGL::turnLeft()
{
    current_direction = current_direction == NORTH? WEST : current_direction == WEST? SOUTH : current_direction == SOUTH? EAST : NORTH;
    updateGL();
    update();
}

void displayGL::turnRight()
{
    current_direction = current_direction == NORTH? EAST: current_direction == EAST? SOUTH : current_direction == SOUTH? WEST: NORTH;
    updateGL();
    update();
}

void displayGL::PickUpItem()
{
    // space bar sets the bool to true if there are items in the room
    int num_items_here = the_rooms.rooms[current_level][current_room]->getItems().size();

    // removes item from room and puts it in player's inventory
    // on screen list will appear with ability to select item to pick
    // return will select the item
    // left right keys will select items
    if (num_items_here > 0)
    {
        in_rm_inventory = true;
        item_at = 0; // space bar resets to the first item in the vector
    }
}

void displayGL::DropItem()
{
    // adds item to room
    // on screen list will appear with ability to select item to drop
    int num_items = thePlayer.getItems().size();
    if (num_items > 0)
    {
        in_inventory = true;
        item_at = 0;
    }
}

void displayGL::checkifwon()
{
    (thePlayer.hasItem(theItems.itemlist["orb_win"])) && (Evil->winToServer());
}

bool displayGL::showitems(QPainter *painter)
{
    uint item_size = the_rooms.rooms[current_level][current_room]->getItems().size();
    for (uint i = 0; i < item_size; i++)
    {
        QString filename =  the_rooms.rooms[current_level][current_room]->getItems()[i]->getId();
        filename.append(".png");
        painter->drawImage(this->width()/2,this->height()/1.1,QImage(QString(filename)));
    }
    return true;
}

bool displayGL::drawEnemies(vector< vector <int> >& Enemies, QPainter *painter)
{
    double high = this->height()/2;
    double wide = this->width()/2;
    QImage troll("./troll.png"); // gotta make this related to what user selects at some point
    // room id depth
    int Num_Enemies = Enemies.size();
    for (int i = 0; i < Num_Enemies; i++)
    {
        double newsize = (600*1.0/((Enemies[i][2]+1)*1.0));
        painter->drawImage(wide, high, troll.scaledToHeight(newsize));
    }
    update();
    return true;
}

bool displayGL::drawMonsters(vector< vector <int> >& Monsters, QPainter *painter)
{
    // room type depth
    double high = this->height()/2;
    double wide = this->width()/2;
    int Num_Monsters = Monsters.size();
    QImage zombie("./zombie.png"); // gotta make this related to what user selects at some point
    for (int i = 0; i < Num_Monsters; i++)
    {
        double newsize = (600*1.0/((Monsters[i][2]+1)*1.0));
        painter->drawImage(wide, high, zombie.scaledToHeight(newsize));
    }
    update();
    return true;
}

bool displayGL::drawQuestion(int current_level, int current_room, QPainter *painter)
{
    in_question = true;

    // we must have a question in this room at this level or else this would not get here
    QRect QuestionRect(20,20,this->width()-40, this->height()/2.5);
    QPen borderpen (Qt::green);
    borderpen.setWidth(3);
    QBrush questionbrush(Qt::lightGray);
    questionbrush.setStyle(Qt::SolidPattern);
    painter->fillRect(QuestionRect, questionbrush);
    painter->setPen(borderpen);
    painter->drawRect(QuestionRect);

    painter->setPen(Qt::white);
    painter->setFont(QFont("Times", 20));
    double QRLeft = QuestionRect.left();
    double QRTop = QuestionRect.top();
    painter->drawText(QRLeft+5, QRTop+5, QuestionRect.width()-10, QuestionRect.height()-10,
                      Qt::AlignHCenter|Qt::TextWordWrap,
                      the_rooms.rooms[current_level][current_room]->getQuestions()[0]->theQuestion);
    // The only question in the room... for now
    num_answers = the_rooms.rooms[current_level][current_room]->getQuestions()[0]->questionanswers.size();

    for (int i = 0; i < num_answers; i++)
    {
        painter->setPen(Qt::darkBlue);
        painter->setFont(QFont("Times", 14));
        painter->drawText(QRLeft+20, QRTop+25+((i+1)*20), QuestionRect.width()-30, QuestionRect.height()-20,
                          Qt::AlignHCenter|Qt::TextWordWrap,
                          the_rooms.rooms[current_level][current_room]->getQuestions()[0]->questionanswers[i]);
    }
    update();
    return true;
}

bool displayGL::answerQuestion(int ans)
{
    // answers the question attaches the stat to the player and deletes the question.
    // it has already checked for appropriateness of the answer
    thePlayer.addStat(the_rooms.rooms[current_level][current_room]->getQuestions()[0]->questionstats[ans]);
    the_rooms.rooms[current_level][current_room]->delQuestion(1);
    update();
    return true;
}

bool displayGL::showthisitem(QPainter *painter)
{
    uint item_size = the_rooms.rooms[current_level][current_room]->getItems().size();
    if (item_at >= 0 && item_at < item_size)
    {
        QString filename = the_rooms.rooms[current_level][current_room]->getItems()[item_at]->getId();
        filename.append(".png");
        QRect bg((this->width()/2)-20, (this->height()/2)-20, 100, 100); // a square to put the item in
        QBrush bgbrush(Qt::black);
        QPen bgoutline(Qt::darkGray);
        bgoutline.setWidth(2);
        painter->setPen(bgoutline);
        painter->fillRect(bg, bgbrush);
        painter->drawRect(bg); // outline the box
        painter->drawImage(this->width()/2,this->height()/2,QImage(QString(filename)).scaledToWidth(60));
        painter->drawText((width()/2)-20, (this->height()/2)+80, 100, 100, Qt::AlignHCenter|Qt::TextWordWrap,
                          the_rooms.rooms[current_level][current_room]->getItems()[item_at]->getName());

    }
    return true;
}

bool displayGL::showmyitem(QPainter *painter)
{
    uint item_size = thePlayer.getItems().size();
    if (item_at >= 0 && item_at < item_size)
    {
        QString filename = thePlayer.getItems()[item_at]->getId();
        filename.append(".png");
        QRect bg(width()-120, 20, 100, 100); // a square to put the item in
        QBrush bgbrush(Qt::darkGreen);
        QPen bgoutline(Qt::darkGray);
        bgoutline.setWidth(2);
        painter->setPen(bgoutline);
        painter->fillRect(bg, bgbrush);
        painter->drawRect(bg); // outline the box
        painter->drawImage(width()-105,40,QImage(QString(filename)).scaledToWidth(60));
        painter->drawText(width()-120, 120, 100, 100, Qt::AlignHCenter|Qt::TextWordWrap,
                          thePlayer.getItems()[item_at]->getName());
    }
    return true;
}

void displayGL::showminimap()
{
    show_map = !show_map;
}

void displayGL::attack()
{
    for (int i = 0; i < 5; i++)
        (MonsterPointers[i]->getRoom() == current_room) && (MonsterPointers[i]->TakeDamage(thePlayer.getStat("Damage")));

    vector<int> damage_who;
    for (int i = 0; i < PlayerLocations.size(); i++)
    {
        if (PlayerLocations[i].first == current_room && PlayerLocations[i].second != myServerSocket)
        {
            qDebug() << "PL" << PlayerLocations[i].second << " SOCKET: " << myServerSocket << endl;
            damage_who.push_back(PlayerLocations[i].second); // damage everyone in the room except myself
        }
    }
    if (damage_who.size() == 0)
        return;
    QString dmg_player;
    // DAMAGE::#dmg-ID,ID,ID...
    dmg_player = QString::number(thePlayer.getStat("Damage"));
    dmg_player.append(tr("-"));
    for (int i = 0; i < damage_who.size(); i++)
    {
        if (i) dmg_player.append(tr(","));
        dmg_player.append(damage_who[i]);
    }
    qDebug() << "DAMAGE WHO: "  << damage_who.size() << endl;
    Evil->damageToServer(dmg_player);
}

bool displayGL::showminimap(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QRect minimap(width()-height()/5, height()-height()/5,height()/5,height()/5);
    QPen borderpen(Qt::gray);
    borderpen.setWidth(3);
    QBrush minimapbrush(Qt::black);
    painter->setBrush(minimapbrush);
    painter->fillRect(minimap,minimapbrush);
    painter->setPen(borderpen);
    painter->drawRect(minimap);
    QPen Player0(Qt::red);
    QPen RoomPen(Qt::gray);
    RoomPen.setWidth(15);
    Player0.setWidth(12);
    uint k = 9; // starting
    double starting_x = width()-height()/5.1 + 10;
    double starting_y;
    for (uint i = 1; i < 7; i++)
    { // done constraints
        starting_y = height()-21;
        for (uint j = 0; j < 6; j++)
        {
            painter->setPen(RoomPen);
            painter->drawPoint(starting_x,starting_y-(j*21));

            QMutex thisMutex;
            thisMutex.lock();
            QVector< pair<int,int> > temp(PlayerLocations); // ROOM LOC, PLAYERID (THREADED SOCKET IDS, SENT BY SERVER SO UNIQUE)
            thisMutex.unlock();
            for (int m = 0; m < temp.size(); m++)
            {
                if (temp[m].first == k)
                {
                    QPen Player1;
                    if (!(m%2))
                        Player1.setColor(QColor((m+3), (m+3), (m+3)*50));
                    else if (!(m%3))
                        Player1.setColor(QColor((m+3)*50, (m+3), (m+3)*50));
                    else if (!(m%5))
                        Player1.setColor(QColor((m+3), (m+3)*30, (m+3)));
                    Player1.setWidth(12);
                    painter->setPen(Player1);
                    painter->drawPoint(starting_x,starting_y-(j*21));
                }
            }
            // show myself, yes have in program
            if (current_room == k)
            {
                painter->setPen(Player0);
                painter->drawPoint(starting_x,starting_y-(j*21));
            }
            k++;
        }
        starting_x = starting_x + 21;
        k+=2;
    }
    return true;
}

void displayGL::doNothing()
{
    // nada
}
