/// This file will be included multiple times
#pragma once

#include <vector>
namespace nncv {
namespace compiler {
namespace utils {

template<typename _Ty>
class GeneralDag;

template<typename _Ty>
struct DagNode;

template<typename _Ty>
struct DagNode {
  // TODO Constructor

  inline _Ty* SelfPtr() { return static_cast<_Ty*>(this); }
  inline const _Ty* SelfConstPtr() const { return static_cast<const _Ty*>(this); }
  inline _Ty& SelfRef() { return static_cast<_Ty&>(*this); }
  inline const _Ty& SelfConstRef() const { return static_cast<const _Ty&>(*this); }

  DagNode<_Ty>* PointTo(DagNode<_Ty>* _rhs) {
    // TODO
    m_OutDegrees++;
    _rhs->m_InDegrees++;
    return _rhs;
  }

 private:
  int m_InDegrees;
  int m_OutDegrees;
  GeneralDag<_Ty>* m_BelongToGraph;
};

template<typename _Ty>
class GeneralDag {
  friend DagNode<_Ty>;

 public:
  // TODO Constructor and Deconsturctor

  void Register(DagNode<_Ty>* _value) {
    m_nodes.emplace_back(_value);
    _value->m_BelongToGraph = this;
    // TODO
  }

 private:
  std::vector<DagNode<_Ty>*> m_nodes;
};

}  // namespace utils
}  // namespace compiler
}  // namespace nncv
