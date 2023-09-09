'在线渲染: https://www.planttext.com/'
'使用文档: https://plantuml.com/zh/sequence-diagram'


@startuml

title monitor更新osd_map(发布订阅)

osd -> osd: OSD启动 \n\
void OSD::start_boot


librados -> librados: monc初始化
monc -> monc: monclient.set_messenger(messenger)

monc -> mon: 与mon建立链接


monc -> mon: 订阅 sub_want, renew_subs, CEPH_MSG_OSD_MAP



mon -> monc: check_sub 向单个订阅者发送最新的map
monc -> monc: 收到monitor更新 MonClient::ms_dispatch \n\
ms_dispatch -> handle_osd_map



@enduml
