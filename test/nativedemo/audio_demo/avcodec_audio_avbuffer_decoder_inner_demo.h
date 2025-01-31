/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#ifndef AVCODEC_AUDIO_AVBUFFER_DECODER_INNER_DEMO_H
#define AVCODEC_AUDIO_AVBUFFER_DECODER_INNER_DEMO_H

#include <atomic>
#include <fstream>
#include <thread>
#include <queue>
#include <string>
#include "avcodec_common.h"
#include "avcodec_audio_codec.h"
#include "buffer/avbuffer.h"
#include "buffer/avbuffer_queue.h"
#include "buffer/avbuffer_queue_consumer.h"
#include "buffer/avbuffer_queue_define.h"
#include "nocopyable.h"

namespace OHOS {
namespace MediaAVCodec {
namespace InnerAudioDemo {

class AudioDecInnerAvBufferDemo {
public:
    AudioDecInnerAvBufferDemo() = default;
    virtual ~AudioDecInnerAvBufferDemo() = default;
    void RunCase();
    void InputFunc();
    void OutputFunc();

private:
    int32_t GetInputBufferSize();
    int32_t fileSize_ = 0;
    std::atomic<int32_t> bufferConsumerAvailableCount_ = 0;
    std::atomic<bool> isRunning_ = false;
    std::unique_ptr<std::ifstream> testFile_;
    std::shared_ptr<AVCodecAudioCodec> audiocodec_;
    std::shared_ptr<Media::AVBufferQueue> innerBufferQueue_;
    sptr<Media::AVBufferQueueConsumer> implConsumer_;
    sptr<Media::AVBufferQueueProducer> mediaCodecProducer_;
    std::unique_ptr<std::ifstream> inputFile_;
    std::unique_ptr<std::ofstream> outputFile_;
};

class AudioCodecConsumerListener : public OHOS::Media::IConsumerListener {
public:
    explicit AudioCodecConsumerListener(AudioDecInnerAvBufferDemo *demo);

    void OnBufferAvailable() override;

private:
    AudioDecInnerAvBufferDemo *demo_;
};

} // namespace InnerAudioDemo
} // namespace MediaAVCodec
} // namespace OHOS
#endif // AVCODEC_AUDIO_AVBUFFER_DECODER_INNER_DEMO_H
