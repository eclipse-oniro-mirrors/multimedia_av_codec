/*
 * Copyright (c) 2024-2024 Huawei Device Co., Ltd.
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

#ifndef DASH_MPD_NODE_H
#define DASH_MPD_NODE_H

#include <cstdint>
#include "i_dash_mpd_node.h"
#include "mpd_parser_def.h"

namespace OHOS {
namespace Media {
namespace Plugins {
namespace HttpPlugin {
class DashMpdNode : public IDashMpdNode {
public:
    DashMpdNode();
    ~DashMpdNode() override;

    void ParseNode(std::shared_ptr<XmlParser> xmlParser, std::shared_ptr<XmlElement> rootElement) override;
    void GetAttr(const std::string &attrName, std::string &sAttrVal) override;
    void GetAttr(const std::string &attrName, uint32_t &uiAttrVal) override;
    void GetAttr(const std::string &attrName, int32_t &iAttrVal) override;
    void GetAttr(const std::string &attrName, uint64_t &ullAttrVal) override;
    void GetAttr(const std::string &attrName, double &dAttrVal) override;

private:
    static constexpr int32_t DASH_MPD_ATTR_NUM = 15;
    static constexpr const char *mpdAttrs_[DASH_MPD_ATTR_NUM] = {"id",
                                                                 "profiles",
                                                                 "type",
                                                                 "availabilityStartTime",
                                                                 "availabilityEndTime",
                                                                 "mediaPresentationDuration",
                                                                 "minimumUpdatePeriod",
                                                                 "minBufferTime",
                                                                 "timeShiftBufferDepth",
                                                                 "suggestedPresentationDelay",
                                                                 "maxSegmentDuration",
                                                                 "maxSubsegmentDuration",
                                                                 "mediaType",
                                                                 "hwTotalViewNumber",
                                                                 "hwDefaultViewIndex"};
    NodeAttr mpdAttr_[DASH_MPD_ATTR_NUM];
};
} // namespace HttpPluginLite
} // namespace Plugin
} // namespace Media
} // namespace OHOS
#endif // DASH_MPD_NODE_H
