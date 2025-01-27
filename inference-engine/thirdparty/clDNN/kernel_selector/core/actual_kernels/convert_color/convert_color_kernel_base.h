// Copyright (C) 2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include "kernel_base_opencl.h"
#include "kernel_selector_params.h"
#include <vector>

namespace kernel_selector {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// convert_color_params
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct convert_color_params : public base_params {
    convert_color_params() : base_params(KernelType::CONVERT_COLOR) {}
    color_format input_color_format;
    color_format output_color_format;
    memory_type mem_type;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// convert_color_optional_params
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct convert_color_optional_params : optional_params {
    convert_color_optional_params() : optional_params(KernelType::CONVERT_COLOR) {}
};

struct convert_color_fuse_params : fuse_params {
    convert_color_fuse_params() : fuse_params(KernelType::CONVERT_COLOR) {}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ConvertColorKernelBase
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ConvertColorKernelBase : public KernelBaseOpenCL {
public:
    using KernelBaseOpenCL::KernelBaseOpenCL;
    virtual ~ConvertColorKernelBase() {}

    struct DispatchData : public CommonDispatchData {};

protected:
    bool Validate(const Params&, const optional_params&) const override;
    virtual JitConstants GetJitConstants(const convert_color_params& params) const;
    virtual CommonDispatchData SetDefault(const convert_color_params& params, const optional_params&) const;
    KernelsData GetCommonKernelsData(const Params& params, const optional_params&) const;
};
}  // namespace kernel_selector
