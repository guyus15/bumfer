#ifndef BUMFER_WIDGET_H
#define BUMFER_WIDGET_H

class Widget
{
public:
    Widget()
    {
        Initialise();
    }

    virtual ~Widget()
    {
        Dispose();
    }

    virtual void Initialise(){};
    virtual void Update(){};
    virtual void Dispose(){};
};

#endif // BUMFER_WIDGET_H
