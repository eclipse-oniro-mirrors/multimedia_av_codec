/*
 * Copyright (c) 2022-2022 Huawei Device Co., Ltd.
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

#ifndef HISTREAMER_M3U8_H
#define HISTREAMER_M3U8_H

#include <memory>
#include <string>
#include <list>
#include <unordered_map>
#include <functional>
#include <map>
#include "hls_tags.h"
#include "playlist_downloader.h"
#include "download/downloader.h"

namespace OHOS {
namespace Media {
namespace Plugins {
namespace HttpPlugin {
enum class M3U8MediaType : int32_t {
    M3U8_MEDIA_TYPE_INVALID = -1,
    M3U8_MEDIA_TYPE_AUDIO,
    M3U8_MEDIA_TYPE_VIDEO,
    M3U8_MEDIA_TYPE_SUBTITLES,
    M3U8_MEDIA_TYPE_CLOSED_CAPTIONS,
    M3U8_N_MEDIA_TYPES,
};

struct M3U8InitFile {
    std::string uri;
    int offset;
    int size;
};

struct M3U8Fragment {
    M3U8Fragment(std::string uri, double duration, int sequence, bool discont);
    M3U8Fragment(const M3U8Fragment& m3u8, const uint8_t *key, const uint8_t *iv);
    std::string uri_;
    double duration_;
    int64_t sequence_;
    bool discont_ {false};
    uint8_t key_[16] { 0 };
    int iv_[16] {0};
    int offset_ {-1};
    int size_ {0};
};

struct M3U8Info {
    std::string uri;
    double duration = 0;
    bool discontinuity = false;
    bool bVod {false};
};

struct M3U8 {
    M3U8(std::string uri, std::string name);
    ~M3U8();
    void InitTagUpdaters();
    void InitTagUpdatersMap();
    bool Update(const std::string& playList, bool isNeedCleanFiles);
    void UpdateFromTags(std::list<std::shared_ptr<Tag>>& tags);
    void GetExtInf(const std::shared_ptr<Tag>& tag, double& duration) const;
    double GetDuration() const;
    bool IsLive() const;

    std::string uri_;
    std::string name_;
    std::unordered_map<HlsTag, std::function<void(std::shared_ptr<Tag>&, M3U8Info&)>> tagUpdatersMap_;

    double targetDuration_ {0.0};
    bool bLive_ {};
    std::list<std::shared_ptr<M3U8Fragment>> files_;
    uint64_t sequence_ {1}; // default 1
    int discontSequence_ {0};
    std::string playList_;
    void ParseKey(const std::shared_ptr<AttributesTag> &tag);
    void DownloadKey();
    bool SaveData(uint8_t *data, uint32_t len);
    static void OnDownloadStatus(DownloadStatus status, std::shared_ptr<Downloader> &,
        std::shared_ptr<DownloadRequest> &request);
    bool SetDrmInfo(std::multimap<std::string, std::vector<uint8_t>>& drmInfo);
    void StoreDrmInfos(const std::multimap<std::string, std::vector<uint8_t>>& drmInfo);
    void ProcessDrmInfos(void);

    std::shared_ptr<std::string> method_;
    std::shared_ptr<std::string> keyUri_;
    uint8_t iv_[16] { 0 };
    uint8_t key_[16] { 0 };
    size_t keyLen_ { 0 };
    std::shared_ptr<Downloader> downloader_;
    std::shared_ptr<DownloadRequest> downloadRequest_;
    DataSaveFunc dataSave_;
    StatusCallbackFunc statusCallback_;
    PlayListChangeCallback *callback_ { nullptr };
    bool startedDownloadStatus_ { false };
    bool isDecryptAble_ { false };
    bool isDecryptKeyReady_ { false };
    std::multimap<std::string, std::vector<uint8_t>> localDrmInfos_;
    M3U8Info firstFragment_;
    std::atomic<bool> isFirstFragmentReady_ {false};
};

struct M3U8Media {
    M3U8MediaType type_;
    std::string groupID_;
    std::string name_;
    std::string lang_;
    std::string uri_;
    bool isDefault_;
    bool autoSelect_;
    bool forced_;
    std::shared_ptr<M3U8> m3u8_;
};

struct M3U8VariantStream {
    M3U8VariantStream(std::string name, std::string uri, std::shared_ptr<M3U8> m3u8);
    std::string name_;
    std::string uri_;
    std::string codecs_;
    uint64_t bandWidth_ {};
    int programID_ {};
    int width_ {};
    int height_ {};
    bool iframe_ {false};
    std::shared_ptr<M3U8> m3u8_;
    std::list<M3U8Media> media_;
};

struct M3U8MasterPlaylist {
    M3U8MasterPlaylist(const std::string& playList, const std::string& uri);
    void UpdateMediaPlaylist();
    void UpdateMasterPlaylist();
    void DownloadSessionKey(std::shared_ptr<Tag>& tag);
    std::list<std::shared_ptr<M3U8VariantStream>> variants_;
    std::shared_ptr<M3U8VariantStream> defaultVariant_;
    std::string uri_;
    std::string playList_;
    double duration_ {0};
    std::atomic<bool> isSimple_ {false};
    std::atomic<bool> bLive_ {false};
    bool isDecryptAble_ { false };
    bool isDecryptKeyReady_ { false };
    uint8_t iv_[16] { 0 };
    uint8_t key_[16] { 0 };
    size_t keyLen_ { 0 };
};
}
}
}
}
#endif