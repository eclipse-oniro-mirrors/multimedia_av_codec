/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FFMPEG_FLAC_ENCODER_PLUGIN_H
#define FFMPEG_FLAC_ENCODER_PLUGIN_H

#include "plugin/codec_plugin.h"
#include "plugin/plugin_definition.h"
#include "ffmpeg_base_encoder.h"

namespace OHOS {
namespace Media {
namespace Plugins {
namespace Ffmpeg {
class FFmpegFlacEncoderPlugin : public CodecPlugin {
public:
    explicit FFmpegFlacEncoderPlugin(const std::string& name);

    ~FFmpegFlacEncoderPlugin();

    Status Init() override;
    Status Reset() override;
    Status Start() override;
    Status Stop() override;
    Status Release() override;
    Status Flush() override;
    Status SetParameter(const std::shared_ptr<Meta> &parameter) override;
    Status GetParameter(std::shared_ptr<Meta> &parameter) override;
    Status QueueInputBuffer(const std::shared_ptr<AVBuffer> &inputBuffer) override;
    Status QueueOutputBuffer(std::shared_ptr<AVBuffer> &outBuffer) override;
    Status GetInputBuffers(std::vector<std::shared_ptr<AVBuffer>> &inputBuffers) override;
    Status GetOutputBuffers(std::vector<std::shared_ptr<AVBuffer>> &outputBuffers) override;

    Status SetDataCallback(DataCallback *dataCallback) override
    {
        dataCallback_ = dataCallback;
        basePlugin->SetCallback(dataCallback_);
        return Status::OK;
    }

private:
    Status CheckFormat(const std::shared_ptr<Meta> &format);
    bool CheckBitRate(const std::shared_ptr<Meta> &format) const;
    Status SetContext(const std::shared_ptr<Meta> &format);
    void SetFormat(const std::shared_ptr<Meta> &format) noexcept;
    int32_t GetInputBufferSize();
    int32_t GetOutputBufferSize();
    int32_t channels_;
    Meta audioParameter_ ;
    DataCallback *dataCallback_{nullptr};
    std::unique_ptr<FFmpegBaseEncoder> basePlugin;
};
} // namespace Ffmpeg
} // namespace Plugins
} // namespace Media
} // namespace OHOS

#endif // FFMPEG_FLAC_ENCODER_PLUGIN_H