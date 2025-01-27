# Copyright (C) 2018-2021 Intel Corporation
# SPDX-License-Identifier: Apache-2.0

import numpy as np

from openvino.tools.mo.ops.priorbox_clustered import PriorBoxClusteredOp
from openvino.tools.mo.front.extractor import FrontExtractorOp
from openvino.tools.mo.front.onnx.extractors.utils import onnx_attr


class PriorBoxClusteredFrontExtractor(FrontExtractorOp):
    op = 'PriorBoxClustered'
    enabled = True

    @classmethod
    def extract(cls, node):
        variance = onnx_attr(node, 'variance', 'floats', default=[], dst_type=lambda x: np.array(x, dtype=np.float32))
        if len(variance) == 0:
            variance = [0.1]

        update_attrs = {
            'width': onnx_attr(node, 'width', 'floats', dst_type=lambda x: np.array(x, dtype=np.float32)),
            'height': onnx_attr(node, 'height', 'floats', dst_type=lambda x: np.array(x, dtype=np.float32)),
            'flip': onnx_attr(node, 'flip', 'i', default=0),
            'clip': onnx_attr(node, 'clip', 'i', default=0),
            'variance': list(variance),
            'img_size': onnx_attr(node, 'img_size', 'i', default=0),
            'img_h': onnx_attr(node, 'img_h', 'i', default=0),
            'img_w': onnx_attr(node, 'img_w', 'i', default=0),
            'step': onnx_attr(node, 'step', 'f', default=0.0),
            'step_h': onnx_attr(node, 'step_h', 'f', default=0.0),
            'step_w': onnx_attr(node, 'step_w', 'f', default=0.0),
            'offset': onnx_attr(node, 'offset', 'f', default=0.0),
        }

        # update the attributes of the node
        PriorBoxClusteredOp.update_node_stat(node, update_attrs)
        return cls.enabled
