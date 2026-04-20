/*
    Elypson/qt-collapsible-section
    (c) 2016 Michael A. Voelkel - michael.alexander.voelkel@gmail.com

    This file is part of Elypson/qt-collapsible section.

    Elypson/qt-collapsible-section is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Elypson/qt-collapsible-section is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Elypson/qt-collapsible-section. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SECTION_H
#define SECTION_H

#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>


    class Section : public QWidget
    {
        Q_OBJECT
        
    private:
        QGridLayout* mainLayout=nullptr;
        QToolButton* toggleButton=nullptr;
        QFrame* headerLine=nullptr;
        QParallelAnimationGroup* toggleAnimation=nullptr;
        QScrollArea* contentArea=nullptr;
        int animationDuration=0;
        int collapsedHeight=0;
        bool isExpanded = false;
        
    public slots:
        void toggle(bool collapsed){ //when collapsed is true
        toggleButton->setArrowType(collapsed ? Qt::ArrowType::DownArrow : Qt::ArrowType::RightArrow);
        toggleAnimation->setDirection(collapsed? QAbstractAnimation::Forward : QAbstractAnimation::Backward);
        toggleAnimation->start();
        
        this->isExpanded = collapsed;
        
        qDebug() << "MV: toggle: isExpanded " << isExpanded;
    }

    public:
        static const int DEFAULT_DURATION = 0;
    
        // initialize section
        explicit Section(const QString& title = "", const int animationDuration = DEFAULT_DURATION, QWidget* parent = nullptr);

        // set layout of content
        void setContentLayout(QLayout& contentLayout);
        
        // set title
        void setTitle(QString title);
        
        // update animations and their heights
        void updateHeights();
    ~Section(){
        if(mainLayout){
            delete mainLayout;
            mainLayout=nullptr;
        }
        if(toggleButton){
            delete toggleButton;
            toggleButton=nullptr;
        }
        if(headerLine){
            delete headerLine;
            headerLine=nullptr;
        }
        if(toggleAnimation){
            delete toggleAnimation;
            toggleAnimation=nullptr;
        }
        if(contentArea){
            delete contentArea;
            contentArea=nullptr;
        }
    }
    };


#endif // SECTION_H
