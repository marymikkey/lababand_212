#ifndef IMP_H
#define IMP_H

#include<QWidget>

class IO : public QWidget {
    Q_OBJECT
public:
    IO(QWidget* parent = nullptr);
    ~IO();

    virtual QString save() = 0;
    virtual void load(QString input);
        private:

};


#endif // IMP_H
