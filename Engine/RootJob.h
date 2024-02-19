#include"GameObject.h"

class RootJob :public GameObject
{
public:
	  RootJob(GameObject*parent);
	  ~RootJob();
	  void Initialize() override;
	  void Update(const float& dt) override;
	  void Draw() override;
	  void Release() override;

};
