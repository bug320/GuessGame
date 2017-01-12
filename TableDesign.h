#ifndef _TableDesign_Second_
#define _TableDesign_Second_
#include <iostream>
#include <map>

template <class TypeId , class TypeFunc >
class TableDesign{
public:
	/* 对外调用的唯一接口函数 */
	static TableDesign* instance()
	{
		if (NULL==s_pInstance)
			s_pInstance=new TableDesign();
		return s_pInstance;
	}
	/*返回自身容器*/
	std::map<TypeId,TypeFunc> Self()
	{
		return m_tdMap;
	}
	/* 向容器内添加对应（id，pfunc）对 */
	void add(TypeId id,TypeFunc pfunc)
	{
		m_tdMap[id]=pfunc;
	}
	/* 返回对应id的pfunc函数，如果没有记录该id则返回NULL */
	TypeFunc pFunc(TypeId id)
	{
		if (m_tdMap.end()==m_tdMap.find(id)){
			return NULL;
		}
		return m_tdMap[id];
	}
protected:
	/* 用来存放表的容器：map */
	std::map<TypeId,TypeFunc>m_tdMap;
	/* 构造函数 */
	TableDesign(){}
	/* 析构函数 */
	virtual~TableDesign()
	{
		//delete s_pInstance;
		//s_pInstance=NULL;
	}
private:
	static TableDesign* s_pInstance;
};
template<class TypeId,class TypeFunc>
TableDesign<TypeId,TypeFunc>* TableDesign<TypeId,TypeFunc>::s_pInstance=NULL;
#endif