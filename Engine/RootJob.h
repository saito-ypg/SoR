#include"GameObject.h"

class RootJob :public GameObject
{
public:
	  RootJob(GameObject*parent);
	  ~RootJob();
	  void SetDelta(float dt);
	  void Initialize() override;
	  void Update() override;
	  void Draw() override;
	  void Release() override;

};
