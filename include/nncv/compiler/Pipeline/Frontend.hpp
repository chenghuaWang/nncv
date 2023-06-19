#ifndef NNCV_COMPILER_TEN_LANG_PIP_FRO_HPP_
#define NNCV_COMPILER_TEN_LANG_PIP_FRO_HPP_

#include <string>

namespace nncv {
namespace compiler {
namespace pipeline {

class pipelineAll {};

class pipeline {
 public:
  virtual void Do() = 0;
};

class FrontendPipeline : public pipeline {
 public:
  void Do() override;

  inline void SetFilePath(const std::string& _CurPath) { m_CurrentFilePath = _CurPath; }

 private:
  std::string m_CurrentFilePath;
};

}  // namespace pipeline
}  // namespace compiler
}  // namespace nncv

#endif  // !NNCV_COMPILER_TEN_LANG_PIP_FRO_HPP_