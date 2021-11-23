from pybindgen import Module, FileCodeSink, param, retval, cppclass, typehandlers


import pybindgen.settings
import warnings

class ErrorHandler(pybindgen.settings.ErrorHandler):
    def handle_error(self, wrapper, exception, traceback_):
        warnings.warn("exception %r in wrapper %s" % (exception, wrapper))
        return True
pybindgen.settings.error_handler = ErrorHandler()


import sys

def module_init():
    root_module = Module('ns.wimax', cpp_namespace='::ns3')
    return root_module

def register_types(module):
    root_module = module.get_root()
    
    ## ul-job.h (module 'wimax'): ns3::ReqType [enumeration]
    module.add_enum('ReqType', ['DATA', 'UNICAST_POLLING'])
    ## log.h (module 'core'): ns3::LogLevel [enumeration]
    module.add_enum('LogLevel', ['LOG_NONE', 'LOG_ERROR', 'LOG_LEVEL_ERROR', 'LOG_WARN', 'LOG_LEVEL_WARN', 'LOG_DEBUG', 'LOG_LEVEL_DEBUG', 'LOG_INFO', 'LOG_LEVEL_INFO', 'LOG_FUNCTION', 'LOG_LEVEL_FUNCTION', 'LOG_LOGIC', 'LOG_LEVEL_LOGIC', 'LOG_ALL', 'LOG_LEVEL_ALL', 'LOG_PREFIX_FUNC', 'LOG_PREFIX_TIME', 'LOG_PREFIX_NODE', 'LOG_PREFIX_LEVEL', 'LOG_PREFIX_ALL'], import_from_module='ns.core')
    ## address.h (module 'network'): ns3::Address [class]
    module.add_class('Address', import_from_module='ns.network')
    ## address.h (module 'network'): ns3::Address::MaxSize_e [enumeration]
    module.add_enum('MaxSize_e', ['MAX_SIZE'], outer_class=root_module['ns3::Address'], import_from_module='ns.network')
    ## trace-helper.h (module 'network'): ns3::AsciiTraceHelper [class]
    module.add_class('AsciiTraceHelper', import_from_module='ns.network')
    ## trace-helper.h (module 'network'): ns3::AsciiTraceHelperForDevice [class]
    module.add_class('AsciiTraceHelperForDevice', import_from_module='ns.network', allow_subclassing=True)
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList [class]
    module.add_class('AttributeConstructionList', import_from_module='ns.core')
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item [struct]
    module.add_class('Item', import_from_module='ns.core', outer_class=root_module['ns3::AttributeConstructionList'])
    typehandlers.add_type_alias('std::list< ns3::AttributeConstructionList::Item > const_iterator', 'ns3::AttributeConstructionList::CIterator')
    typehandlers.add_type_alias('std::list< ns3::AttributeConstructionList::Item > const_iterator*', 'ns3::AttributeConstructionList::CIterator*')
    typehandlers.add_type_alias('std::list< ns3::AttributeConstructionList::Item > const_iterator&', 'ns3::AttributeConstructionList::CIterator&')
    ## buffer.h (module 'network'): ns3::Buffer [class]
    module.add_class('Buffer', import_from_module='ns.network')
    ## buffer.h (module 'network'): ns3::Buffer::Iterator [class]
    module.add_class('Iterator', import_from_module='ns.network', outer_class=root_module['ns3::Buffer'])
    ## packet.h (module 'network'): ns3::ByteTagIterator [class]
    module.add_class('ByteTagIterator', import_from_module='ns.network')
    ## packet.h (module 'network'): ns3::ByteTagIterator::Item [class]
    module.add_class('Item', import_from_module='ns.network', outer_class=root_module['ns3::ByteTagIterator'])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList [class]
    module.add_class('ByteTagList', import_from_module='ns.network')
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator [class]
    module.add_class('Iterator', import_from_module='ns.network', outer_class=root_module['ns3::ByteTagList'])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item [struct]
    module.add_class('Item', import_from_module='ns.network', outer_class=root_module['ns3::ByteTagList::Iterator'])
    ## callback.h (module 'core'): ns3::CallbackBase [class]
    module.add_class('CallbackBase', import_from_module='ns.core')
    ## cid.h (module 'wimax'): ns3::Cid [class]
    module.add_class('Cid')
    ## cid.h (module 'wimax'): ns3::Cid::Type [enumeration]
    module.add_enum('Type', ['BROADCAST', 'INITIAL_RANGING', 'BASIC', 'PRIMARY', 'TRANSPORT', 'MULTICAST', 'PADDING'], outer_class=root_module['ns3::Cid'])
    ## cid-factory.h (module 'wimax'): ns3::CidFactory [class]
    module.add_class('CidFactory')
    ## cs-parameters.h (module 'wimax'): ns3::CsParameters [class]
    module.add_class('CsParameters')
    ## cs-parameters.h (module 'wimax'): ns3::CsParameters::Action [enumeration]
    module.add_enum('Action', ['ADD', 'REPLACE', 'DELETE'], outer_class=root_module['ns3::CsParameters'])
    ## dl-mac-messages.h (module 'wimax'): ns3::DcdChannelEncodings [class]
    module.add_class('DcdChannelEncodings', allow_subclassing=True)
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::AttributeAccessor> [struct]
    module.add_class('DefaultDeleter', import_from_module='ns.core', template_parameters=['ns3::AttributeAccessor'])
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::AttributeChecker> [struct]
    module.add_class('DefaultDeleter', import_from_module='ns.core', template_parameters=['ns3::AttributeChecker'])
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::AttributeValue> [struct]
    module.add_class('DefaultDeleter', import_from_module='ns.core', template_parameters=['ns3::AttributeValue'])
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::CallbackImplBase> [struct]
    module.add_class('DefaultDeleter', import_from_module='ns.core', template_parameters=['ns3::CallbackImplBase'])
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::EventImpl> [struct]
    module.add_class('DefaultDeleter', import_from_module='ns.core', template_parameters=['ns3::EventImpl'])
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::Hash::Implementation> [struct]
    module.add_class('DefaultDeleter', import_from_module='ns.core', template_parameters=['ns3::Hash::Implementation'])
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::NixVector> [struct]
    module.add_class('DefaultDeleter', import_from_module='ns.core', template_parameters=['ns3::NixVector'])
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::OutputStreamWrapper> [struct]
    module.add_class('DefaultDeleter', import_from_module='ns.core', template_parameters=['ns3::OutputStreamWrapper'])
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::Packet> [struct]
    module.add_class('DefaultDeleter', import_from_module='ns.core', template_parameters=['ns3::Packet'])
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::TraceSourceAccessor> [struct]
    module.add_class('DefaultDeleter', import_from_module='ns.core', template_parameters=['ns3::TraceSourceAccessor'])
    ## ofdm-downlink-frame-prefix.h (module 'wimax'): ns3::DlFramePrefixIe [class]
    module.add_class('DlFramePrefixIe')
    ## event-id.h (module 'core'): ns3::EventId [class]
    module.add_class('EventId', import_from_module='ns.core')
    ## hash.h (module 'core'): ns3::Hasher [class]
    module.add_class('Hasher', import_from_module='ns.core')
    ## ipcs-classifier-record.h (module 'wimax'): ns3::IpcsClassifierRecord [class]
    module.add_class('IpcsClassifierRecord')
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address [class]
    module.add_class('Ipv4Address', import_from_module='ns.network')
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address [class]
    root_module['ns3::Ipv4Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask [class]
    module.add_class('Ipv4Mask', import_from_module='ns.network')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address [class]
    module.add_class('Ipv6Address', import_from_module='ns.network')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address [class]
    root_module['ns3::Ipv6Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix [class]
    module.add_class('Ipv6Prefix', import_from_module='ns.network')
    ## log.h (module 'core'): ns3::LogComponent [class]
    module.add_class('LogComponent', import_from_module='ns.core')
    typehandlers.add_type_alias('std::map< std::string, ns3::LogComponent * >', 'ns3::LogComponent::ComponentList')
    typehandlers.add_type_alias('std::map< std::string, ns3::LogComponent * >*', 'ns3::LogComponent::ComponentList*')
    typehandlers.add_type_alias('std::map< std::string, ns3::LogComponent * >&', 'ns3::LogComponent::ComponentList&')
    ## mac48-address.h (module 'network'): ns3::Mac48Address [class]
    module.add_class('Mac48Address', import_from_module='ns.network')
    typehandlers.add_type_alias('void ( * ) ( ns3::Mac48Address )', 'ns3::Mac48Address::TracedCallback')
    typehandlers.add_type_alias('void ( * ) ( ns3::Mac48Address )*', 'ns3::Mac48Address::TracedCallback*')
    typehandlers.add_type_alias('void ( * ) ( ns3::Mac48Address )&', 'ns3::Mac48Address::TracedCallback&')
    ## mac48-address.h (module 'network'): ns3::Mac48Address [class]
    root_module['ns3::Mac48Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## mac8-address.h (module 'network'): ns3::Mac8Address [class]
    module.add_class('Mac8Address', import_from_module='ns.network')
    ## mac8-address.h (module 'network'): ns3::Mac8Address [class]
    root_module['ns3::Mac8Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## net-device-container.h (module 'network'): ns3::NetDeviceContainer [class]
    module.add_class('NetDeviceContainer', import_from_module='ns.network')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::NetDevice > > const_iterator', 'ns3::NetDeviceContainer::Iterator')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::NetDevice > > const_iterator*', 'ns3::NetDeviceContainer::Iterator*')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::NetDevice > > const_iterator&', 'ns3::NetDeviceContainer::Iterator&')
    ## node-container.h (module 'network'): ns3::NodeContainer [class]
    module.add_class('NodeContainer', import_from_module='ns.network')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::Node > > const_iterator', 'ns3::NodeContainer::Iterator')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::Node > > const_iterator*', 'ns3::NodeContainer::Iterator*')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::Node > > const_iterator&', 'ns3::NodeContainer::Iterator&')
    ## object-base.h (module 'core'): ns3::ObjectBase [class]
    module.add_class('ObjectBase', import_from_module='ns.core', allow_subclassing=True)
    ## object.h (module 'core'): ns3::ObjectDeleter [struct]
    module.add_class('ObjectDeleter', import_from_module='ns.core')
    ## object-factory.h (module 'core'): ns3::ObjectFactory [class]
    module.add_class('ObjectFactory', import_from_module='ns.core')
    ## dl-mac-messages.h (module 'wimax'): ns3::OfdmDcdChannelEncodings [class]
    module.add_class('OfdmDcdChannelEncodings', parent=root_module['ns3::DcdChannelEncodings'])
    ## dl-mac-messages.h (module 'wimax'): ns3::OfdmDlBurstProfile [class]
    module.add_class('OfdmDlBurstProfile')
    ## dl-mac-messages.h (module 'wimax'): ns3::OfdmDlBurstProfile::Diuc [enumeration]
    module.add_enum('Diuc', ['DIUC_STC_ZONE', 'DIUC_BURST_PROFILE_1', 'DIUC_BURST_PROFILE_2', 'DIUC_BURST_PROFILE_3', 'DIUC_BURST_PROFILE_4', 'DIUC_BURST_PROFILE_5', 'DIUC_BURST_PROFILE_6', 'DIUC_BURST_PROFILE_7', 'DIUC_BURST_PROFILE_8', 'DIUC_BURST_PROFILE_9', 'DIUC_BURST_PROFILE_10', 'DIUC_BURST_PROFILE_11', 'DIUC_GAP', 'DIUC_END_OF_MAP'], outer_class=root_module['ns3::OfdmDlBurstProfile'])
    ## dl-mac-messages.h (module 'wimax'): ns3::OfdmDlMapIe [class]
    module.add_class('OfdmDlMapIe')
    ## ul-mac-messages.h (module 'wimax'): ns3::OfdmUlBurstProfile [class]
    module.add_class('OfdmUlBurstProfile')
    ## ul-mac-messages.h (module 'wimax'): ns3::OfdmUlBurstProfile::Uiuc [enumeration]
    module.add_enum('Uiuc', ['UIUC_INITIAL_RANGING', 'UIUC_REQ_REGION_FULL', 'UIUC_REQ_REGION_FOCUSED', 'UIUC_FOCUSED_CONTENTION_IE', 'UIUC_BURST_PROFILE_5', 'UIUC_BURST_PROFILE_6', 'UIUC_BURST_PROFILE_7', 'UIUC_BURST_PROFILE_8', 'UIUC_BURST_PROFILE_9', 'UIUC_BURST_PROFILE_10', 'UIUC_BURST_PROFILE_11', 'UIUC_BURST_PROFILE_12', 'UIUC_SUBCH_NETWORK_ENTRY', 'UIUC_END_OF_MAP'], outer_class=root_module['ns3::OfdmUlBurstProfile'])
    ## ul-mac-messages.h (module 'wimax'): ns3::OfdmUlMapIe [class]
    module.add_class('OfdmUlMapIe')
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata [class]
    module.add_class('PacketMetadata', import_from_module='ns.network')
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item [struct]
    module.add_class('Item', import_from_module='ns.network', outer_class=root_module['ns3::PacketMetadata'])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::ItemType [enumeration]
    module.add_enum('ItemType', ['PAYLOAD', 'HEADER', 'TRAILER'], outer_class=root_module['ns3::PacketMetadata::Item'], import_from_module='ns.network')
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::ItemIterator [class]
    module.add_class('ItemIterator', import_from_module='ns.network', outer_class=root_module['ns3::PacketMetadata'])
    ## packet.h (module 'network'): ns3::PacketTagIterator [class]
    module.add_class('PacketTagIterator', import_from_module='ns.network')
    ## packet.h (module 'network'): ns3::PacketTagIterator::Item [class]
    module.add_class('Item', import_from_module='ns.network', outer_class=root_module['ns3::PacketTagIterator'])
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList [class]
    module.add_class('PacketTagList', import_from_module='ns.network')
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData [struct]
    module.add_class('TagData', import_from_module='ns.network', outer_class=root_module['ns3::PacketTagList'])
    ## log.h (module 'core'): ns3::ParameterLogger [class]
    module.add_class('ParameterLogger', import_from_module='ns.core')
    ## pcap-file.h (module 'network'): ns3::PcapFile [class]
    module.add_class('PcapFile', import_from_module='ns.network')
    ## trace-helper.h (module 'network'): ns3::PcapHelper [class]
    module.add_class('PcapHelper', import_from_module='ns.network')
    ## trace-helper.h (module 'network'): ns3::PcapHelper::DataLinkType [enumeration]
    module.add_enum('DataLinkType', ['DLT_NULL', 'DLT_EN10MB', 'DLT_PPP', 'DLT_RAW', 'DLT_IEEE802_11', 'DLT_LINUX_SLL', 'DLT_PRISM_HEADER', 'DLT_IEEE802_11_RADIO', 'DLT_IEEE802_15_4', 'DLT_NETLINK'], outer_class=root_module['ns3::PcapHelper'], import_from_module='ns.network')
    ## trace-helper.h (module 'network'): ns3::PcapHelperForDevice [class]
    module.add_class('PcapHelperForDevice', import_from_module='ns.network', allow_subclassing=True)
    ## snr-to-block-error-rate-manager.h (module 'wimax'): ns3::SNRToBlockErrorRateManager [class]
    module.add_class('SNRToBlockErrorRateManager')
    ## snr-to-block-error-rate-record.h (module 'wimax'): ns3::SNRToBlockErrorRateRecord [class]
    module.add_class('SNRToBlockErrorRateRecord')
    ## ss-record.h (module 'wimax'): ns3::SSRecord [class]
    module.add_class('SSRecord')
    ## send-params.h (module 'wimax'): ns3::SendParams [class]
    module.add_class('SendParams')
    ## service-flow.h (module 'wimax'): ns3::ServiceFlow [class]
    module.add_class('ServiceFlow')
    ## service-flow.h (module 'wimax'): ns3::ServiceFlow::Direction [enumeration]
    module.add_enum('Direction', ['SF_DIRECTION_DOWN', 'SF_DIRECTION_UP'], outer_class=root_module['ns3::ServiceFlow'])
    ## service-flow.h (module 'wimax'): ns3::ServiceFlow::Type [enumeration]
    module.add_enum('Type', ['SF_TYPE_PROVISIONED', 'SF_TYPE_ADMITTED', 'SF_TYPE_ACTIVE'], outer_class=root_module['ns3::ServiceFlow'])
    ## service-flow.h (module 'wimax'): ns3::ServiceFlow::SchedulingType [enumeration]
    module.add_enum('SchedulingType', ['SF_TYPE_NONE', 'SF_TYPE_UNDEF', 'SF_TYPE_BE', 'SF_TYPE_NRTPS', 'SF_TYPE_RTPS', 'SF_TYPE_UGS', 'SF_TYPE_ALL'], outer_class=root_module['ns3::ServiceFlow'])
    ## service-flow.h (module 'wimax'): ns3::ServiceFlow::CsSpecification [enumeration]
    module.add_enum('CsSpecification', ['ATM', 'IPV4', 'IPV6', 'ETHERNET', 'VLAN', 'IPV4_OVER_ETHERNET', 'IPV6_OVER_ETHERNET', 'IPV4_OVER_VLAN', 'IPV6_OVER_VLAN'], outer_class=root_module['ns3::ServiceFlow'])
    ## service-flow.h (module 'wimax'): ns3::ServiceFlow::ModulationType [enumeration]
    module.add_enum('ModulationType', ['MODULATION_TYPE_BPSK_12', 'MODULATION_TYPE_QPSK_12', 'MODULATION_TYPE_QPSK_34', 'MODULATION_TYPE_QAM16_12', 'MODULATION_TYPE_QAM16_34', 'MODULATION_TYPE_QAM64_23', 'MODULATION_TYPE_QAM64_34'], outer_class=root_module['ns3::ServiceFlow'])
    ## service-flow-record.h (module 'wimax'): ns3::ServiceFlowRecord [class]
    module.add_class('ServiceFlowRecord')
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter> [class]
    module.add_class('SimpleRefCount', import_from_module='ns.core', memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'), automatic_type_narrowing=True, parent=root_module['ns3::ObjectBase'], template_parameters=['ns3::Object', 'ns3::ObjectBase', 'ns3::ObjectDeleter'])
    ## simulator.h (module 'core'): ns3::Simulator [class]
    module.add_class('Simulator', import_from_module='ns.core', destructor_visibility='private')
    ## simulator.h (module 'core'): ns3::Simulator [enumeration]
    module.add_enum('', ['NO_CONTEXT'], outer_class=root_module['ns3::Simulator'], import_from_module='ns.core')
    ## tag.h (module 'network'): ns3::Tag [class]
    module.add_class('Tag', import_from_module='ns.network', parent=root_module['ns3::ObjectBase'])
    ## tag-buffer.h (module 'network'): ns3::TagBuffer [class]
    module.add_class('TagBuffer', import_from_module='ns.network')
    ## nstime.h (module 'core'): ns3::Time [class]
    module.add_class('Time', import_from_module='ns.core')
    ## nstime.h (module 'core'): ns3::Time::Unit [enumeration]
    module.add_enum('Unit', ['Y', 'D', 'H', 'MIN', 'S', 'MS', 'US', 'NS', 'PS', 'FS', 'LAST', 'AUTO'], outer_class=root_module['ns3::Time'], import_from_module='ns.core')
    typehandlers.add_type_alias('void ( * ) ( ns3::Time )', 'ns3::Time::TracedCallback')
    typehandlers.add_type_alias('void ( * ) ( ns3::Time )*', 'ns3::Time::TracedCallback*')
    typehandlers.add_type_alias('void ( * ) ( ns3::Time )&', 'ns3::Time::TracedCallback&')
    ## nstime.h (module 'core'): ns3::TimeWithUnit [class]
    module.add_class('TimeWithUnit', import_from_module='ns.core')
    ## wimax-tlv.h (module 'wimax'): ns3::TlvValue [class]
    module.add_class('TlvValue', allow_subclassing=True)
    ## wimax-tlv.h (module 'wimax'): ns3::TosTlvValue [class]
    module.add_class('TosTlvValue', parent=root_module['ns3::TlvValue'])
    ## type-id.h (module 'core'): ns3::TypeId [class]
    module.add_class('TypeId', import_from_module='ns.core')
    ## type-id.h (module 'core'): ns3::TypeId::AttributeFlag [enumeration]
    module.add_enum('AttributeFlag', ['ATTR_GET', 'ATTR_SET', 'ATTR_CONSTRUCT', 'ATTR_SGC'], outer_class=root_module['ns3::TypeId'], import_from_module='ns.core')
    ## type-id.h (module 'core'): ns3::TypeId::SupportLevel [enumeration]
    module.add_enum('SupportLevel', ['SUPPORTED', 'DEPRECATED', 'OBSOLETE'], outer_class=root_module['ns3::TypeId'], import_from_module='ns.core')
    ## type-id.h (module 'core'): ns3::TypeId::AttributeInformation [struct]
    module.add_class('AttributeInformation', import_from_module='ns.core', outer_class=root_module['ns3::TypeId'])
    ## type-id.h (module 'core'): ns3::TypeId::TraceSourceInformation [struct]
    module.add_class('TraceSourceInformation', import_from_module='ns.core', outer_class=root_module['ns3::TypeId'])
    typehandlers.add_type_alias('uint32_t', 'ns3::TypeId::hash_t')
    typehandlers.add_type_alias('uint32_t*', 'ns3::TypeId::hash_t*')
    typehandlers.add_type_alias('uint32_t&', 'ns3::TypeId::hash_t&')
    ## wimax-tlv.h (module 'wimax'): ns3::U16TlvValue [class]
    module.add_class('U16TlvValue', parent=root_module['ns3::TlvValue'])
    ## wimax-tlv.h (module 'wimax'): ns3::U32TlvValue [class]
    module.add_class('U32TlvValue', parent=root_module['ns3::TlvValue'])
    ## wimax-tlv.h (module 'wimax'): ns3::U8TlvValue [class]
    module.add_class('U8TlvValue', parent=root_module['ns3::TlvValue'])
    ## ul-mac-messages.h (module 'wimax'): ns3::UcdChannelEncodings [class]
    module.add_class('UcdChannelEncodings', allow_subclassing=True)
    ## wimax-tlv.h (module 'wimax'): ns3::VectorTlvValue [class]
    module.add_class('VectorTlvValue', parent=root_module['ns3::TlvValue'])
    typehandlers.add_type_alias('std::vector< ns3::Tlv * > const_iterator', 'ns3::VectorTlvValue::Iterator')
    typehandlers.add_type_alias('std::vector< ns3::Tlv * > const_iterator*', 'ns3::VectorTlvValue::Iterator*')
    typehandlers.add_type_alias('std::vector< ns3::Tlv * > const_iterator&', 'ns3::VectorTlvValue::Iterator&')
    ## wimax-helper.h (module 'wimax'): ns3::WimaxHelper [class]
    module.add_class('WimaxHelper', parent=[root_module['ns3::PcapHelperForDevice'], root_module['ns3::AsciiTraceHelperForDevice']])
    ## wimax-helper.h (module 'wimax'): ns3::WimaxHelper::NetDeviceType [enumeration]
    module.add_enum('NetDeviceType', ['DEVICE_TYPE_SUBSCRIBER_STATION', 'DEVICE_TYPE_BASE_STATION'], outer_class=root_module['ns3::WimaxHelper'])
    ## wimax-helper.h (module 'wimax'): ns3::WimaxHelper::PhyType [enumeration]
    module.add_enum('PhyType', ['SIMPLE_PHY_TYPE_OFDM'], outer_class=root_module['ns3::WimaxHelper'])
    ## wimax-helper.h (module 'wimax'): ns3::WimaxHelper::SchedulerType [enumeration]
    module.add_enum('SchedulerType', ['SCHED_TYPE_SIMPLE', 'SCHED_TYPE_RTPS', 'SCHED_TYPE_MBQOS'], outer_class=root_module['ns3::WimaxHelper'])
    ## empty.h (module 'core'): ns3::empty [class]
    module.add_class('empty', import_from_module='ns.core')
    ## int64x64-128.h (module 'core'): ns3::int64x64_t [class]
    module.add_class('int64x64_t', import_from_module='ns.core')
    ## int64x64-128.h (module 'core'): ns3::int64x64_t::impl_type [enumeration]
    module.add_enum('impl_type', ['int128_impl', 'cairo_impl', 'ld_impl'], outer_class=root_module['ns3::int64x64_t'], import_from_module='ns.core')
    ## simple-ofdm-send-param.h (module 'wimax'): ns3::simpleOfdmSendParam [class]
    module.add_class('simpleOfdmSendParam')
    ## chunk.h (module 'network'): ns3::Chunk [class]
    module.add_class('Chunk', import_from_module='ns.network', parent=root_module['ns3::ObjectBase'])
    ## wimax-tlv.h (module 'wimax'): ns3::ClassificationRuleVectorTlvValue [class]
    module.add_class('ClassificationRuleVectorTlvValue', parent=root_module['ns3::VectorTlvValue'])
    ## wimax-tlv.h (module 'wimax'): ns3::ClassificationRuleVectorTlvValue::ClassificationRuleTlvType [enumeration]
    module.add_enum('ClassificationRuleTlvType', ['Priority', 'ToS', 'Protocol', 'IP_src', 'IP_dst', 'Port_src', 'Port_dst', 'Index'], outer_class=root_module['ns3::ClassificationRuleVectorTlvValue'])
    ## wimax-tlv.h (module 'wimax'): ns3::CsParamVectorTlvValue [class]
    module.add_class('CsParamVectorTlvValue', parent=root_module['ns3::VectorTlvValue'])
    ## wimax-tlv.h (module 'wimax'): ns3::CsParamVectorTlvValue::Type [enumeration]
    module.add_enum('Type', ['Classifier_DSC_Action', 'Packet_Classification_Rule'], outer_class=root_module['ns3::CsParamVectorTlvValue'])
    ## header.h (module 'network'): ns3::Header [class]
    module.add_class('Header', import_from_module='ns.network', parent=root_module['ns3::Chunk'])
    ## wimax-tlv.h (module 'wimax'): ns3::Ipv4AddressTlvValue [class]
    module.add_class('Ipv4AddressTlvValue', parent=root_module['ns3::TlvValue'])
    ## wimax-tlv.h (module 'wimax'): ns3::Ipv4AddressTlvValue::ipv4Addr [struct]
    module.add_class('ipv4Addr', outer_class=root_module['ns3::Ipv4AddressTlvValue'])
    typehandlers.add_type_alias('std::vector< ns3::Ipv4AddressTlvValue::ipv4Addr > const_iterator', 'ns3::Ipv4AddressTlvValue::Iterator')
    typehandlers.add_type_alias('std::vector< ns3::Ipv4AddressTlvValue::ipv4Addr > const_iterator*', 'ns3::Ipv4AddressTlvValue::Iterator*')
    typehandlers.add_type_alias('std::vector< ns3::Ipv4AddressTlvValue::ipv4Addr > const_iterator&', 'ns3::Ipv4AddressTlvValue::Iterator&')
    ## wimax-mac-header.h (module 'wimax'): ns3::MacHeaderType [class]
    module.add_class('MacHeaderType', parent=root_module['ns3::Header'])
    ## wimax-mac-header.h (module 'wimax'): ns3::MacHeaderType::HeaderType [enumeration]
    module.add_enum('HeaderType', ['HEADER_TYPE_GENERIC', 'HEADER_TYPE_BANDWIDTH'], outer_class=root_module['ns3::MacHeaderType'])
    ## mac-messages.h (module 'wimax'): ns3::ManagementMessageType [class]
    module.add_class('ManagementMessageType', parent=root_module['ns3::Header'])
    ## mac-messages.h (module 'wimax'): ns3::ManagementMessageType::MessageType [enumeration]
    module.add_enum('MessageType', ['MESSAGE_TYPE_UCD', 'MESSAGE_TYPE_DCD', 'MESSAGE_TYPE_DL_MAP', 'MESSAGE_TYPE_UL_MAP', 'MESSAGE_TYPE_RNG_REQ', 'MESSAGE_TYPE_RNG_RSP', 'MESSAGE_TYPE_REG_REQ', 'MESSAGE_TYPE_REG_RSP', 'MESSAGE_TYPE_DSA_REQ', 'MESSAGE_TYPE_DSA_RSP', 'MESSAGE_TYPE_DSA_ACK'], outer_class=root_module['ns3::ManagementMessageType'])
    ## object.h (module 'core'): ns3::Object [class]
    module.add_class('Object', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter >'])
    ## object.h (module 'core'): ns3::Object::AggregateIterator [class]
    module.add_class('AggregateIterator', import_from_module='ns.core', outer_class=root_module['ns3::Object'])
    ## ofdm-downlink-frame-prefix.h (module 'wimax'): ns3::OfdmDownlinkFramePrefix [class]
    module.add_class('OfdmDownlinkFramePrefix', parent=root_module['ns3::Header'])
    ## send-params.h (module 'wimax'): ns3::OfdmSendParams [class]
    module.add_class('OfdmSendParams', parent=root_module['ns3::SendParams'])
    ## ul-mac-messages.h (module 'wimax'): ns3::OfdmUcdChannelEncodings [class]
    module.add_class('OfdmUcdChannelEncodings', parent=root_module['ns3::UcdChannelEncodings'])
    ## packet-burst.h (module 'network'): ns3::PacketBurst [class]
    module.add_class('PacketBurst', import_from_module='ns.network', parent=root_module['ns3::Object'])
    typehandlers.add_type_alias('void ( * ) ( ns3::Ptr< ns3::PacketBurst const > )', 'ns3::PacketBurst::TracedCallback')
    typehandlers.add_type_alias('void ( * ) ( ns3::Ptr< ns3::PacketBurst const > )*', 'ns3::PacketBurst::TracedCallback*')
    typehandlers.add_type_alias('void ( * ) ( ns3::Ptr< ns3::PacketBurst const > )&', 'ns3::PacketBurst::TracedCallback&')
    ## pcap-file-wrapper.h (module 'network'): ns3::PcapFileWrapper [class]
    module.add_class('PcapFileWrapper', import_from_module='ns.network', parent=root_module['ns3::Object'])
    ## wimax-tlv.h (module 'wimax'): ns3::PortRangeTlvValue [class]
    module.add_class('PortRangeTlvValue', parent=root_module['ns3::TlvValue'])
    ## wimax-tlv.h (module 'wimax'): ns3::PortRangeTlvValue::PortRange [struct]
    module.add_class('PortRange', outer_class=root_module['ns3::PortRangeTlvValue'])
    typehandlers.add_type_alias('std::vector< ns3::PortRangeTlvValue::PortRange > const_iterator', 'ns3::PortRangeTlvValue::Iterator')
    typehandlers.add_type_alias('std::vector< ns3::PortRangeTlvValue::PortRange > const_iterator*', 'ns3::PortRangeTlvValue::Iterator*')
    typehandlers.add_type_alias('std::vector< ns3::PortRangeTlvValue::PortRange > const_iterator&', 'ns3::PortRangeTlvValue::Iterator&')
    ## ul-job.h (module 'wimax'): ns3::PriorityUlJob [class]
    module.add_class('PriorityUlJob', parent=root_module['ns3::Object'])
    ## propagation-loss-model.h (module 'propagation'): ns3::PropagationLossModel [class]
    module.add_class('PropagationLossModel', import_from_module='ns.propagation', parent=root_module['ns3::Object'])
    ## wimax-tlv.h (module 'wimax'): ns3::ProtocolTlvValue [class]
    module.add_class('ProtocolTlvValue', parent=root_module['ns3::TlvValue'])
    typehandlers.add_type_alias('std::vector< unsigned char > const_iterator', 'ns3::ProtocolTlvValue::Iterator')
    typehandlers.add_type_alias('std::vector< unsigned char > const_iterator*', 'ns3::ProtocolTlvValue::Iterator*')
    typehandlers.add_type_alias('std::vector< unsigned char > const_iterator&', 'ns3::ProtocolTlvValue::Iterator&')
    ## propagation-loss-model.h (module 'propagation'): ns3::RandomPropagationLossModel [class]
    module.add_class('RandomPropagationLossModel', import_from_module='ns.propagation', parent=root_module['ns3::PropagationLossModel'])
    ## random-variable-stream.h (module 'core'): ns3::RandomVariableStream [class]
    module.add_class('RandomVariableStream', import_from_module='ns.core', parent=root_module['ns3::Object'])
    ## propagation-loss-model.h (module 'propagation'): ns3::RangePropagationLossModel [class]
    module.add_class('RangePropagationLossModel', import_from_module='ns.propagation', parent=root_module['ns3::PropagationLossModel'])
    ## mac-messages.h (module 'wimax'): ns3::RngReq [class]
    module.add_class('RngReq', parent=root_module['ns3::Header'])
    ## mac-messages.h (module 'wimax'): ns3::RngRsp [class]
    module.add_class('RngRsp', parent=root_module['ns3::Header'])
    ## ss-manager.h (module 'wimax'): ns3::SSManager [class]
    module.add_class('SSManager', parent=root_module['ns3::Object'])
    ## random-variable-stream.h (module 'core'): ns3::SequentialRandomVariable [class]
    module.add_class('SequentialRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## service-flow-manager.h (module 'wimax'): ns3::ServiceFlowManager [class]
    module.add_class('ServiceFlowManager', parent=root_module['ns3::Object'])
    ## service-flow-manager.h (module 'wimax'): ns3::ServiceFlowManager::ConfirmationCode [enumeration]
    module.add_enum('ConfirmationCode', ['CONFIRMATION_CODE_SUCCESS', 'CONFIRMATION_CODE_REJECT'], outer_class=root_module['ns3::ServiceFlowManager'])
    ## wimax-tlv.h (module 'wimax'): ns3::SfVectorTlvValue [class]
    module.add_class('SfVectorTlvValue', parent=root_module['ns3::VectorTlvValue'])
    ## wimax-tlv.h (module 'wimax'): ns3::SfVectorTlvValue::Type [enumeration]
    module.add_enum('Type', ['SFID', 'CID', 'Service_Class_Name', 'reserved1', 'QoS_Parameter_Set_Type', 'Traffic_Priority', 'Maximum_Sustained_Traffic_Rate', 'Maximum_Traffic_Burst', 'Minimum_Reserved_Traffic_Rate', 'Minimum_Tolerable_Traffic_Rate', 'Service_Flow_Scheduling_Type', 'Request_Transmission_Policy', 'Tolerated_Jitter', 'Maximum_Latency', 'Fixed_length_versus_Variable_length_SDU_Indicator', 'SDU_Size', 'Target_SAID', 'ARQ_Enable', 'ARQ_WINDOW_SIZE', 'ARQ_RETRY_TIMEOUT_Transmitter_Delay', 'ARQ_RETRY_TIMEOUT_Receiver_Delay', 'ARQ_BLOCK_LIFETIME', 'ARQ_SYNC_LOSS', 'ARQ_DELIVER_IN_ORDER', 'ARQ_PURGE_TIMEOUT', 'ARQ_BLOCK_SIZE', 'reserved2', 'CS_Specification', 'IPV4_CS_Parameters'], outer_class=root_module['ns3::SfVectorTlvValue'])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor>> [class]
    module.add_class('SimpleRefCount', import_from_module='ns.core', memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'), automatic_type_narrowing=True, parent=root_module['ns3::empty'], template_parameters=['ns3::AttributeAccessor', 'ns3::empty', 'ns3::DefaultDeleter<ns3::AttributeAccessor>'])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker>> [class]
    module.add_class('SimpleRefCount', import_from_module='ns.core', memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'), automatic_type_narrowing=True, parent=root_module['ns3::empty'], template_parameters=['ns3::AttributeChecker', 'ns3::empty', 'ns3::DefaultDeleter<ns3::AttributeChecker>'])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue>> [class]
    module.add_class('SimpleRefCount', import_from_module='ns.core', memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'), automatic_type_narrowing=True, parent=root_module['ns3::empty'], template_parameters=['ns3::AttributeValue', 'ns3::empty', 'ns3::DefaultDeleter<ns3::AttributeValue>'])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::CallbackImplBase, ns3::empty, ns3::DefaultDeleter<ns3::CallbackImplBase>> [class]
    module.add_class('SimpleRefCount', import_from_module='ns.core', memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'), automatic_type_narrowing=True, parent=root_module['ns3::empty'], template_parameters=['ns3::CallbackImplBase', 'ns3::empty', 'ns3::DefaultDeleter<ns3::CallbackImplBase>'])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::EventImpl, ns3::empty, ns3::DefaultDeleter<ns3::EventImpl>> [class]
    module.add_class('SimpleRefCount', import_from_module='ns.core', memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'), automatic_type_narrowing=True, parent=root_module['ns3::empty'], template_parameters=['ns3::EventImpl', 'ns3::empty', 'ns3::DefaultDeleter<ns3::EventImpl>'])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Hash::Implementation, ns3::empty, ns3::DefaultDeleter<ns3::Hash::Implementation>> [class]
    module.add_class('SimpleRefCount', import_from_module='ns.core', memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'), automatic_type_narrowing=True, parent=root_module['ns3::empty'], template_parameters=['ns3::Hash::Implementation', 'ns3::empty', 'ns3::DefaultDeleter<ns3::Hash::Implementation>'])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::NixVector, ns3::empty, ns3::DefaultDeleter<ns3::NixVector>> [class]
    module.add_class('SimpleRefCount', import_from_module='ns.core', memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'), automatic_type_narrowing=True, parent=root_module['ns3::empty'], template_parameters=['ns3::NixVector', 'ns3::empty', 'ns3::DefaultDeleter<ns3::NixVector>'])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::OutputStreamWrapper, ns3::empty, ns3::DefaultDeleter<ns3::OutputStreamWrapper>> [class]
    module.add_class('SimpleRefCount', import_from_module='ns.core', memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'), automatic_type_narrowing=True, parent=root_module['ns3::empty'], template_parameters=['ns3::OutputStreamWrapper', 'ns3::empty', 'ns3::DefaultDeleter<ns3::OutputStreamWrapper>'])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Packet, ns3::empty, ns3::DefaultDeleter<ns3::Packet>> [class]
    module.add_class('SimpleRefCount', import_from_module='ns.core', memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'), automatic_type_narrowing=True, parent=root_module['ns3::empty'], template_parameters=['ns3::Packet', 'ns3::empty', 'ns3::DefaultDeleter<ns3::Packet>'])
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor>> [class]
    module.add_class('SimpleRefCount', import_from_module='ns.core', memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'), automatic_type_narrowing=True, parent=root_module['ns3::empty'], template_parameters=['ns3::TraceSourceAccessor', 'ns3::empty', 'ns3::DefaultDeleter<ns3::TraceSourceAccessor>'])
    ## ss-service-flow-manager.h (module 'wimax'): ns3::SsServiceFlowManager [class]
    module.add_class('SsServiceFlowManager', parent=root_module['ns3::ServiceFlowManager'])
    ## ss-service-flow-manager.h (module 'wimax'): ns3::SsServiceFlowManager::ConfirmationCode [enumeration]
    module.add_enum('ConfirmationCode', ['CONFIRMATION_CODE_SUCCESS', 'CONFIRMATION_CODE_REJECT'], outer_class=root_module['ns3::SsServiceFlowManager'])
    ## propagation-loss-model.h (module 'propagation'): ns3::ThreeLogDistancePropagationLossModel [class]
    module.add_class('ThreeLogDistancePropagationLossModel', import_from_module='ns.propagation', parent=root_module['ns3::PropagationLossModel'])
    ## wimax-tlv.h (module 'wimax'): ns3::Tlv [class]
    module.add_class('Tlv', parent=root_module['ns3::Header'])
    ## wimax-tlv.h (module 'wimax'): ns3::Tlv::CommonTypes [enumeration]
    module.add_enum('CommonTypes', ['HMAC_TUPLE', 'MAC_VERSION_ENCODING', 'CURRENT_TRANSMIT_POWER', 'DOWNLINK_SERVICE_FLOW', 'UPLINK_SERVICE_FLOW', 'VENDOR_ID_EMCODING', 'VENDOR_SPECIFIC_INFORMATION'], outer_class=root_module['ns3::Tlv'])
    ## trace-source-accessor.h (module 'core'): ns3::TraceSourceAccessor [class]
    module.add_class('TraceSourceAccessor', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::TraceSourceAccessor, ns3::empty, ns3::DefaultDeleter<ns3::TraceSourceAccessor> >'])
    ## trailer.h (module 'network'): ns3::Trailer [class]
    module.add_class('Trailer', import_from_module='ns.network', parent=root_module['ns3::Chunk'])
    ## random-variable-stream.h (module 'core'): ns3::TriangularRandomVariable [class]
    module.add_class('TriangularRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## propagation-loss-model.h (module 'propagation'): ns3::TwoRayGroundPropagationLossModel [class]
    module.add_class('TwoRayGroundPropagationLossModel', import_from_module='ns.propagation', parent=root_module['ns3::PropagationLossModel'])
    ## ul-mac-messages.h (module 'wimax'): ns3::Ucd [class]
    module.add_class('Ucd', parent=root_module['ns3::Header'])
    ## ul-job.h (module 'wimax'): ns3::UlJob [class]
    module.add_class('UlJob', parent=root_module['ns3::Object'])
    ## ul-job.h (module 'wimax'): ns3::UlJob::JobPriority [enumeration]
    module.add_enum('JobPriority', ['LOW', 'INTERMEDIATE', 'HIGH'], outer_class=root_module['ns3::UlJob'])
    ## ul-mac-messages.h (module 'wimax'): ns3::UlMap [class]
    module.add_class('UlMap', parent=root_module['ns3::Header'])
    ## random-variable-stream.h (module 'core'): ns3::UniformRandomVariable [class]
    module.add_class('UniformRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## bs-uplink-scheduler.h (module 'wimax'): ns3::UplinkScheduler [class]
    module.add_class('UplinkScheduler', parent=root_module['ns3::Object'])
    ## bs-uplink-scheduler-mbqos.h (module 'wimax'): ns3::UplinkSchedulerMBQoS [class]
    module.add_class('UplinkSchedulerMBQoS', parent=root_module['ns3::UplinkScheduler'])
    ## bs-uplink-scheduler-rtps.h (module 'wimax'): ns3::UplinkSchedulerRtps [class]
    module.add_class('UplinkSchedulerRtps', parent=root_module['ns3::UplinkScheduler'])
    ## bs-uplink-scheduler-simple.h (module 'wimax'): ns3::UplinkSchedulerSimple [class]
    module.add_class('UplinkSchedulerSimple', parent=root_module['ns3::UplinkScheduler'])
    ## random-variable-stream.h (module 'core'): ns3::WeibullRandomVariable [class]
    module.add_class('WeibullRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## wimax-connection.h (module 'wimax'): ns3::WimaxConnection [class]
    module.add_class('WimaxConnection', parent=root_module['ns3::Object'])
    typehandlers.add_type_alias('std::list< ns3::Ptr< ns3::Packet const > >', 'ns3::WimaxConnection::FragmentsQueue')
    typehandlers.add_type_alias('std::list< ns3::Ptr< ns3::Packet const > >*', 'ns3::WimaxConnection::FragmentsQueue*')
    typehandlers.add_type_alias('std::list< ns3::Ptr< ns3::Packet const > >&', 'ns3::WimaxConnection::FragmentsQueue&')
    ## wimax-mac-queue.h (module 'wimax'): ns3::WimaxMacQueue [class]
    module.add_class('WimaxMacQueue', parent=root_module['ns3::Object'])
    ## wimax-mac-queue.h (module 'wimax'): ns3::WimaxMacQueue::QueueElement [struct]
    module.add_class('QueueElement', outer_class=root_module['ns3::WimaxMacQueue'])
    ## wimax-mac-to-mac-header.h (module 'wimax'): ns3::WimaxMacToMacHeader [class]
    module.add_class('WimaxMacToMacHeader', parent=root_module['ns3::Header'])
    ## wimax-phy.h (module 'wimax'): ns3::WimaxPhy [class]
    module.add_class('WimaxPhy', parent=root_module['ns3::Object'])
    ## wimax-phy.h (module 'wimax'): ns3::WimaxPhy::ModulationType [enumeration]
    module.add_enum('ModulationType', ['MODULATION_TYPE_BPSK_12', 'MODULATION_TYPE_QPSK_12', 'MODULATION_TYPE_QPSK_34', 'MODULATION_TYPE_QAM16_12', 'MODULATION_TYPE_QAM16_34', 'MODULATION_TYPE_QAM64_23', 'MODULATION_TYPE_QAM64_34'], outer_class=root_module['ns3::WimaxPhy'])
    ## wimax-phy.h (module 'wimax'): ns3::WimaxPhy::PhyState [enumeration]
    module.add_enum('PhyState', ['PHY_STATE_IDLE', 'PHY_STATE_SCANNING', 'PHY_STATE_TX', 'PHY_STATE_RX'], outer_class=root_module['ns3::WimaxPhy'])
    ## wimax-phy.h (module 'wimax'): ns3::WimaxPhy::PhyType [enumeration]
    module.add_enum('PhyType', ['SimpleWimaxPhy', 'simpleOfdmWimaxPhy'], outer_class=root_module['ns3::WimaxPhy'])
    ## random-variable-stream.h (module 'core'): ns3::ZetaRandomVariable [class]
    module.add_class('ZetaRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## random-variable-stream.h (module 'core'): ns3::ZipfRandomVariable [class]
    module.add_class('ZipfRandomVariable', import_from_module='ns.core', parent=root_module['ns3::RandomVariableStream'])
    ## attribute.h (module 'core'): ns3::AttributeAccessor [class]
    module.add_class('AttributeAccessor', import_from_module='ns.core', parent=root_module['ns3::SimpleRefCount< ns3::AttributeAccessor, ns3::empty, ns3::DefaultDeleter<ns3::AttributeAccessor> >'])
    ## attribute.h (module 'core'): ns3::AttributeChecker [class]
    module.add_class('AttributeChecker', import_from_module='ns.core', automatic_type_narrowing=True, allow_subclassing=False, parent=root_module['ns3::SimpleRefCount< ns3::AttributeChecker, ns3::empty, ns3::DefaultDeleter<ns3::AttributeChecker> >'])
    ## attribute.h (module 'core'): ns3::AttributeValue [class]
    module.add_class('AttributeValue', import_from_module='ns.core', automatic_type_narrowing=True, allow_subclassing=False, parent=root_module['ns3::SimpleRefCount< ns3::AttributeValue, ns3::empty, ns3::DefaultDeleter<ns3::AttributeValue> >'])
    ## bs-scheduler.h (module 'wimax'): ns3::BSScheduler [class]
    module.add_class('BSScheduler', parent=root_module['ns3::Object'])
