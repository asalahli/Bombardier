#include "Collision.hpp"

sf::Vector2f perpAxis(const sf::Transform& t, const sf::Vector2f& p1, const sf::Vector2f& p2) {
    sf::Vector2f side = t.transformPoint(p1) - t.transformPoint(p2);
    sf::Vector2f axis = sf::Vector2f(side.y, -side.x);

    return axis;
}

float len2(const sf::Vector2f& v) {
    return v.x*v.x + v.y*v.y;
}

float dot(const sf::Vector2f& v, const sf::Vector2f& w) {
    return v.x*w.x + v.y*w.y;
}

sf::Vector2f normalize(const sf::Vector2f& v) {
    float len = sqrt(len2(v));

    return sf::Vector2f(v.x/len, v.y/len);
}

sf::Vector2f checkProjections(sf::Vector2f& axis, const GameObject* go1, const GameObject* go2) {
    axis = normalize(axis);

    float go1begin = dot(axis, go1->getTransform().transformPoint(go1->boundingPolygon.front()));
    float go1end = dot(axis, go1->getTransform().transformPoint(go1->boundingPolygon.front()));
    for (sf::Vector2f p : go1->boundingPolygon) {
        float go1point = dot(axis, go1->getTransform().transformPoint(p));

        if (go1point < go1begin)
            go1begin = go1point;

        if (go1point > go1end)
            go1end = go1point;
    }

    float go2begin = dot(axis, go2->getTransform().transformPoint(go2->boundingPolygon.front()));
    float go2end = dot(axis, go2->getTransform().transformPoint(go2->boundingPolygon.front()));
    for (sf::Vector2f p : go2->boundingPolygon) {
        float go2point = dot(axis, go2->getTransform().transformPoint(p));

        if (go2point < go2begin)
            go2begin = go2point;

        if (go2point > go2end)
            go2end = go2point;
    }

    float factor;

    if (go1end <= go2begin || go2end <= go1begin) {
        factor = 0;
    }
    else if (go1begin < go2end) {
        factor = go2end - go1begin;
    }
    else {
        factor = go1end - go2begin;
    }

    return factor * axis;
}

sf::Vector2f checkCollision(const GameObject* go1, const GameObject* go2) {
    sf::Transform t1 = go1->getTransform();
    sf::Transform t2 = go2->getTransform();

    bool firstTime = true;
    sf::Vector2f p1, collision(0, 0);

//    std::cerr << "Polygon 1: " << std::endl;

    p1 = go1->boundingPolygon.back();
    for (sf::Vector2f p2 : go1->boundingPolygon) {
//        std::cerr << t1.transformPoint(p1).x << " , "
//                    << t1.transformPoint(p1).y << " : "
//                    << t1.transformPoint(p2).x << " , "
//                    << t1.transformPoint(p2).y << std::endl;

        sf::Vector2f axis = perpAxis(t1, p1, p2);
        sf::Vector2f coll = checkProjections(axis, go1, go2);

        if (firstTime || len2(coll) < len2(collision)) {
            collision = coll;
            firstTime = false;
        }

        p1 = p2;
    }

//    std::cerr << "Polygon 2: " << std::endl;

    p1 = go2->boundingPolygon.back();
    for (sf::Vector2f p2 : go2->boundingPolygon) {
//        std::cerr << t2.transformPoint(p1).x << " , "
//                    << t2.transformPoint(p1).y << " : "
//                    << t2.transformPoint(p2).x << " , "
//                    << t2.transformPoint(p2).y << std::endl;

        sf::Vector2f axis = perpAxis(t2, p1, p2);
        sf::Vector2f coll = checkProjections(axis, go1, go2);

        if (firstTime || len2(coll) < len2(collision)) {
            collision = coll;
            firstTime = false;
        }

        p1 = p2;
    }

    return collision;
}
