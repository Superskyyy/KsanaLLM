/* Copyright 2023 Tencent Inc.  All rights reserved.

==============================================================================*/
#pragma once

#include "numerous_llm/models/base/base_weight.h"
#include "numerous_llm/utils/environment.h"
#include "numerous_llm/utils/utils.h"

namespace numerous_llm {

template <typename T>
class LlamaWeight : public BaseWeight {
 public:
  LlamaWeight() {}
  ~LlamaWeight();
  explicit LlamaWeight(const ModelConfig& model_config, int rank, std::shared_ptr<Context> context);

  Tensor GetModelWeights(const std::string& weight_name);

 private:
  Status LoadWeightFromBin(Tensor tensor, std::string binfile, bool transpose = false);

  Status LoadLlamaWeightsMap(const ModelConfig& model_config);

  std::string ConcatLayerName(std::string layer_flag, int& layer_index);

  std::string GetBinfileName(std::string weight_name);

  Status AddWeightTensor(std::string weight_name, std::vector<size_t> shapes, DataType dtype, bool transpose = false);

  std::unordered_map<std::string, Tensor> weights_map_;

  static std::pair<const char*, const char*> binfile_map_[];

  std::string model_path_ = "";
  int rank_ = 0;

  std::shared_ptr<Context> context_{nullptr};
};

}  // namespace numerous_llm
