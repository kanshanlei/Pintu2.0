#include <stdio.h>
#include <ScoreData.h>
class ScoreStrategy 
{
private:
	int _continues;//����Ҫ��ʾ�Ĺؿ���
public:
	ScoreStrategy();
	virtual void execute(ScoreData* score);
};
