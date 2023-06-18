#ifndef NNCV_COMPILER_TEN_LANG_PIP_FRO_HPP_
#define NNCV_COMPILER_TEN_LANG_PIP_FRO_HPP_

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
};

}  // namespace pipeline
}  // namespace compiler
}  // namespace nncv

#endif  // !NNCV_COMPILER_TEN_LANG_PIP_FRO_HPP_