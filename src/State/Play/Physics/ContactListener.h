#ifndef GRAVITONIUM_CONTACTLISTENER_H
#define GRAVITONIUM_CONTACTLISTENER_H

#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact *);

    void EndContact(b2Contact *);

    void PreSolve(b2Contact *, const b2Manifold *);

    void PostSolve(b2Contact *, const b2ContactImpulse *);
};

#endif //GRAVITONIUM_CONTACTLISTENER_H