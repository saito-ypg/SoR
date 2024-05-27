#include "Ease.h"
#include<cmath>
#include<DirectXMath.h>
using namespace std;
using namespace DirectX;
static float Ease::InSine(float t)
{
    return sinf(XM_PIDIV2 * t);
}

static float Ease::OutSine(float t)
{
    return 1 + sinf(XM_PIDIV2 * (--t));
}

static float Ease::InOutSine(float t)
{
    return 0.5f * (1 + sinf(static_cast<float>(XM_PI) * (t - 0.5f)));
}

static float Ease::InQuad(float t)
{
    return t * t;
}

static float Ease::OutQuad(float t)
{
    return t * (2 - t);
}

static float Ease::InOutQuad(float t)
{
    return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
}

static float Ease::InCubic(float t)
{
    return t * t * t;
}

static float Ease::OutCubic(float t)
{
    return 1 + (--t) * t * t;
}

static float Ease::InOutCubic(float t)
{
    return t < 0.5 ? 4 * t * t * t : 1 + (--t) * (2 * (--t)) * (2 * t);
}

static float Ease::InQuart(float t)
{
    t *= t;
    return t * t;
}

static float Ease::OutQuart(float t)
{
    t = (--t) * t;
    return 1 - t * t;
}

static float Ease::InOutQuart(float t)
{
    if (t < 0.5)
    {
        t *= t;
        return 8 * t * t;
    }
    else
    {
        t = (--t) * t;
        return 1 - 8 * t * t;
    }
}

static float Ease::InQuint(float t)
{
    float t2 = t * t;
    return t * t2 * t2;
}

static float Ease::OutQuint(float t)
{
    float t2 = (--t) * t;
    return 1 + 16 * t * t2 * t2;
}

static float Ease::InOutQuint(float t)
{
    float t2;
    if (t < 0.5)
    {
        t2 = t * t;
        return 16 * t * t2 * t2;
    }
    else
    {
        t2 = (--t) * t;
        return 1 + 16 * t * t2 * t2;
    }
}

static float Ease::InExpo(float t)
{
    return (powf(2, 8 * t) - 1) / 255;
}

static float Ease::OutExpo(float t)
{
    return 1 - powf(2, -8 * t);
}

static float Ease::InOutExpo(float t)
{
    if (t < 0.5)
    {
        return (powf(2, 16 * t) - 1) / 510;
    }
    else
    {
        return 1 - 0.5f * powf(2.0f, -16.0f * (t - 0.5f));
    }
}

static float Ease::InCirc(float t)
{
    return 1.0f - sqrtf(1 - t);
}

static float Ease::OutCirc(float t)
{
    return sqrtf(t);
}

static float Ease::InOutCirc(float t)
{
    if (t < 0.5f)
    {
        return (1.0f - sqrtf(1.0f - 2.0f * t)) * 0.5f;
    }
    else
    {
        return (1.0f + sqrtf(2.0f * t - 1.0f)) * 0.5f;
    }
}

static float Ease::InBack(float t)
{
    return t * t * (2.70158f * t - 1.70158f);
}

static float Ease::OutBack(float t)
{
    return 1 + (--t) * t * (2.70158f * t + 1.70158f);
}

static float Ease::InOutBack(float t)
{
    if (t < 0.5)
    {
        return t * t * (7 * t - 2.5f) * 2;
    }
    else
    {
        return 1 + (--t) * t * 2 * (7 * t + 2.5f);
    }
}

static float Ease::InElastic(float t)
{
    float t2 = t * t;
    return t2 * t2 * sinf(static_cast<float>(t * XM_PI* 4.5f));
}

static float Ease::OutElastic(float t)
{
    float t2 = (t - 1) * (t - 1);
    return 1 - t2 * t2 * cosf(static_cast<float>(t * XM_PI * 4.5f));
}

static float Ease::InOutElastic(float t)
{
    float t2;
    if (t < 0.45)
    {
        t2 = t * t;
        return 8 * t2 * t2 * sinf(static_cast<float>(t * XM_PI * 9));
    }
    else if (t < 0.55)
    {
        return 0.5f + 0.75f * sinf(static_cast<float>(t * XM_PI * 4));
    }
    else
    {
        t2 = (t - 1) * (t - 1);
        return 1 - 8 * t2 * t2 * sinf(static_cast<float>(t * XM_PI * 9));
    }
}

static float Ease::InBounce(float t)
{
    return powf(2, 6 * (t - 1)) * fabs(sinf(static_cast<float>(t * XM_PI * 3.5f)));
}

static float Ease::OutBounce(float t)
{
    return 1 - powf(2, -6 * t) * fabs(cosf(static_cast<float>(t * XM_PI * 3.5)));
}

static float Ease::InOutBounce(float t)
{
    if (t < 0.5)
    {
        return 8 * powf(2, 8 * (t - 1)) * fabs(sinf( static_cast<float>(t *XM_PI * 7)));
    }
    else
    {
        return 1 - 8 * powf(2, -8 * t) * fabs(sinf(static_cast<float>(t * XM_PI * 7)));
    }
}