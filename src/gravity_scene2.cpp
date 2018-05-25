#include "gravity_scene2.h"
#include <QBrush>
#include <QPen>
#include <QTimer>
#include <QPoint>
#include <QKeyEvent>
#include <QDebug>
#include <typeinfo>

gravity_scene::gravity_scene()
{
    time_step = 10;
    g = 0.001;
    Vx = 0.4;
    Vy = 0;
    Width = 720;
    Hight = 540;
    bz = 30;
    pz = 200;

    this->addRect(0,0,Width,Hight,QPen(Qt::red));
    gp_pan1 = this->addRect(0,0,5,pz,QPen(Qt::red),QBrush(Qt::red));
    gp_pan2 = this->addRect(0,0,5,pz,QPen(Qt::red),QBrush(Qt::red));

    gp_ball = this->addEllipse(0,0,bz,bz);
    gp_ball->setBrush(QBrush(Qt::blue));

    scene_timer = new QTimer(this);
    connect(scene_timer,SIGNAL(timeout()),this,SLOT(gp_update()));

    initial();
    scene_timer->start(time_step);
    //qDebug()<<"Eky = "<<Eky;
}

void gravity_scene::initial(){

     Vx = 0.4;
     Vy = 0;
    pan_up = false;
    pan_down = false;

    qreal h = 300;

    gp_pan1->setPos(-5,(Hight-pz)/2);
    gp_pan2->setPos(Width,(Hight-pz)/2);
    gp_ball->setPos(10,Hight-h);
    score = 0;
    Vx = 0.5;
    Vy = 0.1;

    Ekx = Vx*Vx/2;
    Eky = Vy*Vy/2 + g*h;
}

void gravity_scene::keyPressEvent(QKeyEvent * keyEvent){
    if(keyEvent->key() == Qt::Key_Up){
        pan_up = true;
    }

    if(keyEvent->key() == Qt::Key_Down){
        pan_down = true;
    }

    if(keyEvent->key() == Qt::Key_Space){
        initial();
        scene_timer->start(time_step);
    }
}

void gravity_scene::keyReleaseEvent(QKeyEvent * keyEvent){
    if(keyEvent->key() == Qt::Key_Up){
        pan_up = false;
    }

    if(keyEvent->key() == Qt::Key_Down){
        pan_down = false;
    }
}

void gravity_scene::pan_update(){
    qreal ps = pz/20;
    QGraphicsRectItem *gp_pan;
    gp_pan = Vx > 0 ? gp_pan2: gp_pan1;

    if(pan_up){
        QPointF tmp = gp_pan->scenePos();
        if(tmp.y()>ps){
            gp_pan->setPos(tmp.x(),tmp.y()-ps);
        }else gp_pan->setPos(tmp.x(),0);
    }

    if(pan_down){
        QPointF tmp = gp_pan->scenePos();
        if(tmp.y()<Hight-pz-ps){
            gp_pan->setPos(tmp.x(),tmp.y()+ps);
        }else gp_pan->setPos(tmp.x(),Hight-pz);
    }
}

void gravity_scene::ball_update(){
    qreal x,y;
    QPointF tmp = gp_ball->scenePos();

    y = tmp.y()+Vy*time_step+g*time_step*time_step/2;

    if(y >(Hight - bz) or (y<=0)){
        qreal Ky = (Eky - g*(Hight-tmp.y()));
        Ky = Ky < 0 ? 0 : Ky;
        qreal mVy = sqrt(2*Ky);
        if(y <= 0) mVy = -mVy;
        Vy = -mVy+g*(time_step-(mVy-Vy)/g);
        qreal h = (Eky-Vy*Vy/2)/g;
        y = Hight - h;
     }else{
            Vy = Vy + g*time_step;
     }

    x = tmp.x()+Vx*time_step;
    if((x>(Width - bz) && Vx>0) || (x < 0 && Vx<0))
    {
        qreal y_hit = (y+tmp.y())/2;
        QGraphicsRectItem *gp_pan;
        gp_pan = Vx > 0 ? gp_pan2: gp_pan1;

        qreal y_pan = gp_pan->scenePos().y();
        y_pan -= bz/2;
        qreal hit_score = (y_hit-y_pan)/pz;
       // qDebug()<<y_hit<<","<<y_pan<<","<<hit_score;
        qreal r=1.0;
        if(hit_score < 0 or hit_score > 1){
            scene_timer->stop();
            //Vx = -Vx;
        }else if(hit_score <= 0.5){
            r = 1.05;
        }else if(hit_score > 0.5){
            r = 0.95;
        }
        Vx = -Vx*r;
        score++;
    }

    gp_ball->setPos(x,y);
}

void gravity_scene::gp_update()
{

    pan_update();
    ball_update();
    send_message(QString::number(score));
    //qDebug()<<"in gp_update:"<<Vy<<","<<y<<",Ey = "<<g*(Hight-y)+Vy*Vy/2;

}
