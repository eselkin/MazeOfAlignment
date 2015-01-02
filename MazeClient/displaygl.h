#ifndef DISPLAYGL_H
#define DISPLAYGL_H

#if defined(__WIN32__) || defined(__LINUX__)
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

#include <QGLWidget>
#include <QImage>
#include <QKeyEvent>
#include <QMouseEvent>
#include "weights.h"
#include "adjacency.h"
#include "roomlist.h"
#include "allItems.h"
#include "networkofalignment.h"
#include "player.h"
#include "zombie.h"


class displayGL : public QGLWidget
{
    Q_OBJECT
public:
    //(fo.o)f
    typedef void (displayGL::*fptr)();
    explicit displayGL(QString serverID, int serverPort, QWidget *parent = 0);
    ~displayGL();

signals:

public slots:
    void initializeGL();
    //void paintGL();
    void resizeGL(int w, int h);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent( QMouseEvent *e );
    void keyPressEvent(QKeyEvent *e);
    void showInfo(QPainter *toPaint);
    void ChangeLocations(QStringList playerlocations);
    void myGameOver(QString playerID);
    void getServerSocket(int);
    void bornagain();

protected slots:

protected:
    void init_fp();
    void loadTextures();
    bool drawBackWall(int depth, int type, int level);
    bool drawDoor(bool left_right, int start_depth);
    bool drawSideWall(bool left_right, weights *access, int start_depth, int level);
    bool drawRoom(DIRECTION one, DIRECTION two, int my_room, int count_ahead, weights *forward, int depth, int &max_depth, vector<vector<int> > &P_Loc_Sz, vector<vector<int> > &M_Loc_Sz);
    void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);
    bool drawEnemies(vector<vector<int> > &Enemies, QPainter *painter);
    bool drawMonsters(vector<vector<int> > &Monsters, QPainter *painter);
    bool drawQuestion(int current_level, int current_room, QPainter *painter);
    bool answerQuestion(int ans);

private slots:

private:
    NetworkOfAlignment *Evil; // Just for fun, this is the network connection for the client
    roomlist the_rooms;
    QVector< pair<int, int> > PlayerLocations; // int location and int ID of player
    QImage m_images[40];
    GLuint texture_ids[40]; // Texture IDS
    double level_r[7],level_g[7], level_b[7];
    DIRECTION current_direction;
    int current_room, current_level;
    Adjacency adjacencyTable;
    allItems theItems;
    weights* checkAhead(int room_number, int next_room);
    bool checkstats(weights *testForward);
    bool checkitems(weights *testForward);
    int countAhead(DIRECTION dir);
    fptr key_fptrs[128];
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();
    void PickUpItem();
    void DropItem();
    void checkifwon();
    bool in_inventory, in_rm_inventory, in_question;
    int  item_at, num_answers;
    void doNothing();
    bool showmyitem(QPainter *painter);
    bool showitems(QPainter *painter);
    bool showminimap(QPainter *painter);
    bool showthisitem(QPainter *painter);
    void showminimap(); // the function pointer function
    void attack();
    bool show_map;
    player thePlayer;
    int* start_loc;
    int myServerSocket;
    monster* MonsterPointers[10];
};

#endif // DISPLAYGL_H
