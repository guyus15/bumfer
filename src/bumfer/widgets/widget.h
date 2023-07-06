#ifndef BUMFER_WIDGET_H
#define BUMFER_WIDGET_H

class IWidget
{
public:
    IWidget()
    {
        Initialise();
    }

    virtual ~IWidget()
    {
        Dispose();
    }

    virtual void Initialise() {};
    virtual void Update() {};
    virtual void Dispose() {};
};

#endif // BUMFER_WIDGET_H
