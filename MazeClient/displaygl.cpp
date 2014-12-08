#include "displaygl.h"
#include <cmath>
#include <QtOpenGL>
#include <QtGui>
#include <QBrush>
#include <QtCore>
#include <QRect>
#include <QPainter>
#include <QPaintEvent>

#include <GL/gl.h>
#include <GL/glu.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#include <QDebug>
#include <iostream>
#include <QPixmap>
#include <QString>
#include "adjacency.h"
#include "roomlist.h"

using namespace std;

displayGL::displayGL(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    // GOSH, playing media files on Qt is crazy!
    //    Phonon::MediaObject *mediaObject = new Phonon::MediaObject(this);
    //    mediaObject->setCurrentSource(Phonon::MediaSource("./song.wav"));
    //    Phonon::AudioOutput *audioOutput =
    //            new Phonon::AudioOutput(Phonon::MusicCategory, this);
    //    Phonon::Path path = Phonon::createPath(mediaObject, audioOutput);
    //    mediaObject->play();

    Evil =  new NetworkOfAlignment("127.0.0.1",9966);
    connect(Evil, SIGNAL(LocationsChanged(QStringList)), this, SLOT(ChangeLocations(QStringList)));
    setAutoFillBackground(false);
    current_direction = WEST;
    current_level = 1;
    current_room = 17;
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
    key_fptrs[Qt::Key_Space] = &displayGL::PickUpItem;
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
    bool playerahead = false;
    int playerdepth = 0;
    int playerid = 0;

    do {
        my_room = my_room + count_ahead;
        if (current_direction == NORTH)
        {
            drawSideWall(0,checkAhead(my_room,my_room+countAhead(WEST)), i, current_level);
            drawSideWall(1,checkAhead(my_room,my_room+countAhead(EAST)), i, current_level);
            for (int k = 0; k < PlayerLocations.size(); k++)
                (PlayerLocations[k]==my_room && my_room!=current_room) && (playerahead = true) && (playerid = k) && (playerdepth = i);
        }
        else
            if (current_direction == SOUTH)
            {
                drawSideWall(0,checkAhead(my_room,my_room+countAhead(EAST)), i, current_level);
                drawSideWall(1,checkAhead(my_room,my_room+countAhead(WEST)), i, current_level);
                for (int k = 0; k < PlayerLocations.size(); k++)
                    (PlayerLocations[k]==my_room && my_room!=current_room) && (playerahead = true) && (playerid = k) && (playerdepth = i);
            }
            else
                if (current_direction == EAST)
                {
                    drawSideWall(0,checkAhead(my_room,my_room+countAhead(NORTH)), i, current_level);
                    drawSideWall(1,checkAhead(my_room,my_room+countAhead(SOUTH)), i, current_level);
                    for (int k = 0; k < PlayerLocations.size(); k++)
                        (PlayerLocations[k]==my_room && my_room!=current_room) && (playerahead = true) && (playerid = k) && (playerdepth = i);
                }
                else {
                    drawSideWall(0,checkAhead(my_room,my_room+countAhead(SOUTH)), i, current_level);
                    drawSideWall(1,checkAhead(my_room,my_room+countAhead(NORTH)), i, current_level);
                    for (int k = 0; k < PlayerLocations.size(); k++)
                        (PlayerLocations[k]==my_room && my_room!=current_room) && (playerahead = true) && (playerid = k) && (playerdepth = i);
                }
        count_ahead = countAhead(current_direction);
        forward = checkAhead(my_room, my_room+count_ahead);
        i++;
    } while (forward && i < 4 && !forward->isDoor()); // stops at a door, can't see through it
    forward && (drawBackWall(i, forward->isDoor(), current_level));
    !forward && (drawBackWall(i, 0, current_level));
    //(playerahead) && (drawEnemy(playerid, playerdepth, &painter));
    playerdepth = 0;
    playerid = 0;
    playerahead = 0;
    showInfo(&painter); // show the info at the top of the screen
    showitems(&painter); // show available items in the room
    (show_map) && showminimap(&painter); // no ifs or buts, but one and
    (in_rm_inventory) && showthisitem(&painter);
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

    //fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;

    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

void displayGL::mousePressEvent(QMouseEvent *e)
{
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
            //
            ///
            // then add to the player!
            ///
            //

            glFlush();
            in_rm_inventory = false;
            break;
        case Qt::Key_Escape:
            in_rm_inventory = false;
            break;
        }
    } else
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
    toPaint->drawText((width()-rect.width())/2, border, rect.width(), rect.height(),Qt::AlignRight|Qt::TextSingleLine, Info);
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
        PlayerLocations.push_back(player_loc[1].toInt());
    }
    thisMutex.unlock();
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
     *  |  |\  |  /|  |
     *  |  | |-+-| |  |
     * -+--+-+-2-+1+-0+-
     *  |  | |-+-| |  |
     *  |  |/__|__\|  |
     *  | /    |    \ |
     *  |/_____|_____\|
     *         |
     */

    double start_x = wallstops[start_depth] * (left_right ? 1 : -1);
    double end_x = wallstops[start_depth+1] * (left_right ? 1 : -1);
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
        // YADA YADA YADA ... player has adequate stats, items, etc.
        // testForward has the list of items we must check against our inventory
        current_room = current_room + count_ahead;
    }
    Evil->moveToServer(current_room);
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
        // This is where we test if we meet the weights requirement!!!!!!!!!!!!!!!!!!!
        //
        // YADA YADA YADA ... player has adequate stats, items, etc.
        // testForward has the list of items we must check against our inventory
        current_room = current_room + count_ahead;
    }
    Evil->moveToServer(current_room);
    update();
    updateGL();
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
}

bool displayGL::showitems(QPainter *painter)
{
    uint item_size = the_rooms.rooms[current_level][current_room]->getItems().size();
    for (uint i = 0; i < item_size; i++)
    {
        string filename =  the_rooms.rooms[current_level][current_room]->getItems()[i]->getId();
        filename.append(".png");
        painter->drawImage(this->width()/2,this->height()/1.1,QImage(QString(filename.c_str())));
    }
    return true;
}
bool displayGL::drawEnemy(int player, int size, QPainter *painter)
{
    double newsize = 500/size;
    double high = this->height()/2;
    double wide = this->width()/2;
    QImage troll("./weapon_spear.png");
    painter->drawImage(wide, high, troll.scaledToHeight(newsize));
    update();
    return true;
}

bool displayGL::showthisitem(QPainter *painter)
{
    uint item_size = the_rooms.rooms[current_level][current_room]->getItems().size();
    if (item_at >= 0 && item_at < item_size)
    {
        string filename =  the_rooms.rooms[current_level][current_room]->getItems()[item_at]->getId();
        filename.append(".png");
        QRect bg((this->width()/2)-20, (this->height()/2)-20, 100, 100); // a square to put the item in
        QBrush bgbrush(Qt::black);
        QPen bgoutline(Qt::darkGray);
        bgoutline.setWidth(2);
        painter->setPen(bgoutline);
        painter->fillRect(bg, bgbrush);
        painter->drawRect(bg); // outline the box
        painter->drawImage(this->width()/2,this->height()/2,QImage(QString(filename.c_str())).scaledToWidth(60));
    }
    return true;
}

void displayGL::showminimap()
{
    show_map = !show_map;
}

bool displayGL::showminimap(QPainter *painter)
{

    painter->setRenderHint(QPainter::Antialiasing);
    QRect border(width()-height()/5,height()-height()/5, height()/5,height()/5);
    QRect minimap(width()-height()/5.1, height()-height()/5.1,height()/5.1,height()/5.1);
    QBrush borderbrush(Qt::red);
    painter->setBrush(borderbrush);
    painter->fillRect(border, borderbrush);
    QBrush minimapbrush(Qt::black);
    painter->setBrush(minimapbrush);
    painter->fillRect(minimap,minimapbrush);
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
            // ask server to return array of room where Players are
            // if (serverresponse...)


            //
            //            DANGER
            //
            // THIS IS JUST A TEST NOT TO BE USED IN THE GAME!
            //            switch(rand()%5) // give a chance for just grey square
            //            {
            //            case 0:
            //            case 1:
            //                painter->setPen(Player1);
            //                painter->drawPoint(starting_x,starting_y-(j*20));
            //                break;
            //            case 2:
            //                painter->setPen(Player2);
            //                painter->drawPoint(starting_x,starting_y-(j*20));
            //                break;
            //            case 3:
            //                painter->setPen(Player3);
            //                painter->drawPoint(starting_x,starting_y-(j*20));
            //                break;
            //            default:
            //                break;
            //            }
            QMutex thisMutex;
            thisMutex.lock();
            QVector<int> temp(PlayerLocations);
            thisMutex.unlock();
            for (int m = 0; m < temp.size(); m++)
            {
                if (temp[m] == k)
                {
                    qDebug() << "temp[" << m << "]: "<< temp[m] << endl;
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

