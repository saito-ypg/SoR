#include <cmath>
#include <DirectXMath.h>
#include "Ease.h"
namespace EASE {
	using std::unordered_map;
	using std::function;
	using enum easeType;
	using namespace DirectX;

	// すべてのイージング関数を事前に定義する
	double InSineEase(double t) { return sin(XM_PIDIV2 * t); }
	double OutSineEase(double t) { return 1 + sin(XM_PIDIV2 * (--t)); }
	double InOutSineEase(double t) { return 0.5 * (1 + sin(XM_PI * (t - 0.5))); }
	double InQuadEase(double t) { return t * t; }
	double OutQuadEase(double t) { return t * (2 - t); }
	double InOutQuadEase(double t) { return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1; }
	double InCubicEase(double t) { return t * t * t; }
	double OutCubicEase(double t) { return 1 + (--t) * t * t; }
	double InOutCubicEase(double t) { return t < 0.5 ? 4 * t * t * t : 1 + (--t) * (2 * (--t)) * (2 * t); }
	double InQuartEase(double t) { t *= t; return t * t; }
	double OutQuartEase(double t) { t = (--t) * t; return 1 - t * t; }
	double InOutQuartEase(double t) { if (t < 0.5) { t *= t; return 8 * t * t; } else { t = (--t) * t; return 1 - 8 * t * t; } }
	double InQuintEase(double t) { double t2 = t * t; return t * t2 * t2; }
	double InOutQuintEase(double t) { double t2; if (t < 0.5) { t2 = t * t; return 16 * t * t2 * t2; } else { t2 = (--t) * t; return 1 + 16 * t * t2 * t2; } }
	double InExpoEase(double t) { return (pow(2, 8 * t) - 1) / 255; }
	double OutExpoEase(double t) { return 1 - pow(2, -8 * t); }
	double InOutExpoEase(double t) { if (t < 0.5) { return (pow(2, 16 * t) - 1) / 510; } else { return 1 - 0.5 * pow(2, -16 * (t - 0.5)); } }
	double InCircEase(double t) { return 1 - sqrt(1 - t); }
	double OutCircEase(double t) { return sqrt(t); }
	double InOutCircEase(double t) { if (t < 0.5) { return (1 - sqrt(1 - 2 * t)) * 0.5; } else { return (1 + sqrt(2 * t - 1)) * 0.5; } }
	double InBackEase(double t) { return t * t * (2.70158 * t - 1.70158); }
	double OutBackEase(double t) { return 1 + (--t) * t * (2.70158 * t + 1.70158); }
	double InOutBackEase(double t) { if (t < 0.5) { return t * t * (7 * t - 2.5) * 2; } else { return 1 + (--t) * t * 2 * (7 * t + 2.5); } }
	double InElasticEase(double t) { double t2 = t * t; return t2 * t2 * sin(t * XM_PI * 4.5); }
	double OutElasticEase(double t) { double t2 = (t - 1) * (t - 1); return 1 - t2 * t2 * cos(t * XM_PI * 4.5); }
	double InOutElasticEase(double t) { double t2; if (t < 0.45) { t2 = t * t; return 8 * t2 * t2 * sin(t * XM_PI * 9); } else if (t < 0.55) { return 0.5 + 0.75 * sin(t * XM_PI * 4); } else { t2 = (t - 1) * (t - 1); return 1 - 8 * t2 * t2 * sin(t * XM_PI * 9); } }
	double InBounceEase(double t) { return pow(2, 6 * (t - 1)) * abs(sin(t * XM_PI * 3.5)); }
	double OutBounceEase(double t) { return 1 - pow(2, -6 * t) * abs(cos(t * XM_PI * 3.5)); }
	double InOutBounceEase(double t) { if (t < 0.5) { return 8 * pow(2, 8 * (t - 1)) * abs(sin(t * XM_PI * 7)); } else { return 1 - 8 * pow(2, -8 * t) * abs(sin(t * XM_PI * 7)); } }

	// easeListを関数ポインタで定義する
	auto easeList = unordered_map<easeType, double (*)(double)>{
		{InSine, InSineEase},
		{OutSine, OutSineEase},
		{InOutSine, InOutSineEase},
		{InQuad, InQuadEase},
		{OutQuad, OutQuadEase},
		{InOutQuad, InOutQuadEase},
		{InCubic, InCubicEase},
		{OutCubic, OutCubicEase},
		{InOutCubic, InOutCubicEase},
		{InQuart, InQuartEase},
		{OutQuart, OutQuartEase},
		{InOutQuart, InOutQuartEase},
		{InQuint, InQuintEase},
		{InOutQuint, InOutQuintEase},
		{InExpo, InExpoEase},
		{OutExpo, OutExpoEase},
		{InOutExpo, InOutExpoEase},
		{InCirc, InCircEase},
		{OutCirc, OutCircEase},
		{InOutCirc, InOutCircEase},
		{InBack, InBackEase},
		{OutBack, OutBackEase},
		{InOutBack, InOutBackEase},
		{InElastic, InElasticEase},
		{OutElastic, OutElasticEase},
		{InOutElastic, InOutElasticEase},
		{InBounce, InBounceEase},
		{OutBounce, OutBounceEase},
		{InOutBounce,InOutBounceEase}
	};
	double easing(easeType type, double rate)
	{//条件
		if (static_cast<int>(type) < 0 || type >= MAX)
		{
			return std::numeric_limits<double>::quiet_NaN();
		}
		return easeList.at(type)(rate);
	}
};
