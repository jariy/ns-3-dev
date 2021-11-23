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
    root_module = Module('ns.network', cpp_namespace='::ns3')
    return root_module

def register_types(module):
    root_module = module.get_root()
    
    ## packetbb.h (module 'network'): ns3::PbbAddressLength [enumeration]
    module.add_enum('PbbAddressLength', ['IPV4', 'IPV6'])
    ## ethernet-header.h (module 'network'): ns3::ethernet_header_t [enumeration]
    module.add_enum('ethernet_header_t', ['LENGTH', 'VLAN', 'QINQ'])
    ## queue-size.h (module 'network'): ns3::QueueSizeUnit [enumeration]
    module.add_enum('QueueSizeUnit', ['PACKETS', 'BYTES'])
    ## log.h (module 'core'): ns3::LogLevel [enumeration]
    module.add_enum('LogLevel', ['LOG_NONE', 'LOG_ERROR', 'LOG_LEVEL_ERROR', 'LOG_WARN', 'LOG_LEVEL_WARN', 'LOG_DEBUG', 'LOG_LEVEL_DEBUG', 'LOG_INFO', 'LOG_LEVEL_INFO', 'LOG_FUNCTION', 'LOG_LEVEL_FUNCTION', 'LOG_LOGIC', 'LOG_LEVEL_LOGIC', 'LOG_ALL', 'LOG_LEVEL_ALL', 'LOG_PREFIX_FUNC', 'LOG_PREFIX_TIME', 'LOG_PREFIX_NODE', 'LOG_PREFIX_LEVEL', 'LOG_PREFIX_ALL'], import_from_module='ns.core')
    ## address.h (module 'network'): ns3::Address [class]
    module.add_class('Address')
    ## address.h (module 'network'): ns3::Address::MaxSize_e [enumeration]
    module.add_enum('MaxSize_e', ['MAX_SIZE'], outer_class=root_module['ns3::Address'])
    ## application-container.h (module 'network'): ns3::ApplicationContainer [class]
    module.add_class('ApplicationContainer')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::Application > > const_iterator', 'ns3::ApplicationContainer::Iterator')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::Application > > const_iterator*', 'ns3::ApplicationContainer::Iterator*')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::Application > > const_iterator&', 'ns3::ApplicationContainer::Iterator&')
    ## trace-helper.h (module 'network'): ns3::AsciiTraceHelper [class]
    module.add_class('AsciiTraceHelper')
    ## trace-helper.h (module 'network'): ns3::AsciiTraceHelperForDevice [class]
    module.add_class('AsciiTraceHelperForDevice', allow_subclassing=True)
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList [class]
    module.add_class('AttributeConstructionList', import_from_module='ns.core')
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item [struct]
    module.add_class('Item', import_from_module='ns.core', outer_class=root_module['ns3::AttributeConstructionList'])
    typehandlers.add_type_alias('std::list< ns3::AttributeConstructionList::Item > const_iterator', 'ns3::AttributeConstructionList::CIterator')
    typehandlers.add_type_alias('std::list< ns3::AttributeConstructionList::Item > const_iterator*', 'ns3::AttributeConstructionList::CIterator*')
    typehandlers.add_type_alias('std::list< ns3::AttributeConstructionList::Item > const_iterator&', 'ns3::AttributeConstructionList::CIterator&')
    ## buffer.h (module 'network'): ns3::Buffer [class]
    module.add_class('Buffer')
    ## buffer.h (module 'network'): ns3::Buffer::Iterator [class]
    module.add_class('Iterator', outer_class=root_module['ns3::Buffer'])
    ## packet.h (module 'network'): ns3::ByteTagIterator [class]
    module.add_class('ByteTagIterator')
    ## packet.h (module 'network'): ns3::ByteTagIterator::Item [class]
    module.add_class('Item', outer_class=root_module['ns3::ByteTagIterator'])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList [class]
    module.add_class('ByteTagList')
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator [class]
    module.add_class('Iterator', outer_class=root_module['ns3::ByteTagList'])
    ## byte-tag-list.h (module 'network'): ns3::ByteTagList::Iterator::Item [struct]
    module.add_class('Item', outer_class=root_module['ns3::ByteTagList::Iterator'])
    ## callback.h (module 'core'): ns3::CallbackBase [class]
    module.add_class('CallbackBase', import_from_module='ns.core')
    ## channel-list.h (module 'network'): ns3::ChannelList [class]
    module.add_class('ChannelList')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::Channel > > const_iterator', 'ns3::ChannelList::Iterator')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::Channel > > const_iterator*', 'ns3::ChannelList::Iterator*')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::Channel > > const_iterator&', 'ns3::ChannelList::Iterator&')
    ## data-output-interface.h (module 'stats'): ns3::DataOutputCallback [class]
    module.add_class('DataOutputCallback', import_from_module='ns.stats', allow_subclassing=True)
    ## data-rate.h (module 'network'): ns3::DataRate [class]
    module.add_class('DataRate')
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
    module.add_class('DefaultDeleter', template_parameters=['ns3::NixVector'])
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::OutputStreamWrapper> [struct]
    module.add_class('DefaultDeleter', template_parameters=['ns3::OutputStreamWrapper'])
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::Packet> [struct]
    module.add_class('DefaultDeleter', template_parameters=['ns3::Packet'])
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::PbbAddressBlock> [struct]
    module.add_class('DefaultDeleter', template_parameters=['ns3::PbbAddressBlock'])
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::PbbMessage> [struct]
    module.add_class('DefaultDeleter', template_parameters=['ns3::PbbMessage'])
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::PbbTlv> [struct]
    module.add_class('DefaultDeleter', template_parameters=['ns3::PbbTlv'])
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::QueueItem> [struct]
    module.add_class('DefaultDeleter', template_parameters=['ns3::QueueItem'])
    ## default-deleter.h (module 'core'): ns3::DefaultDeleter<ns3::TraceSourceAccessor> [struct]
    module.add_class('DefaultDeleter', import_from_module='ns.core', template_parameters=['ns3::TraceSourceAccessor'])
    ## delay-jitter-estimation.h (module 'network'): ns3::DelayJitterEstimation [class]
    module.add_class('DelayJitterEstimation')
    ## event-id.h (module 'core'): ns3::EventId [class]
    module.add_class('EventId', import_from_module='ns.core')
    ## hash.h (module 'core'): ns3::Hasher [class]
    module.add_class('Hasher', import_from_module='ns.core')
    ## inet6-socket-address.h (module 'network'): ns3::Inet6SocketAddress [class]
    module.add_class('Inet6SocketAddress')
    ## inet6-socket-address.h (module 'network'): ns3::Inet6SocketAddress [class]
    root_module['ns3::Inet6SocketAddress'].implicitly_converts_to(root_module['ns3::Address'])
    ## inet-socket-address.h (module 'network'): ns3::InetSocketAddress [class]
    module.add_class('InetSocketAddress')
    ## inet-socket-address.h (module 'network'): ns3::InetSocketAddress [class]
    root_module['ns3::InetSocketAddress'].implicitly_converts_to(root_module['ns3::Address'])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address [class]
    module.add_class('Ipv4Address')
    ## ipv4-address.h (module 'network'): ns3::Ipv4Address [class]
    root_module['ns3::Ipv4Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## ipv4-address.h (module 'network'): ns3::Ipv4Mask [class]
    module.add_class('Ipv4Mask')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address [class]
    module.add_class('Ipv6Address')
    ## ipv6-address.h (module 'network'): ns3::Ipv6Address [class]
    root_module['ns3::Ipv6Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## ipv6-address.h (module 'network'): ns3::Ipv6Prefix [class]
    module.add_class('Ipv6Prefix')
    ## log.h (module 'core'): ns3::LogComponent [class]
    module.add_class('LogComponent', import_from_module='ns.core')
    typehandlers.add_type_alias('std::map< std::string, ns3::LogComponent * >', 'ns3::LogComponent::ComponentList')
    typehandlers.add_type_alias('std::map< std::string, ns3::LogComponent * >*', 'ns3::LogComponent::ComponentList*')
    typehandlers.add_type_alias('std::map< std::string, ns3::LogComponent * >&', 'ns3::LogComponent::ComponentList&')
    ## mac16-address.h (module 'network'): ns3::Mac16Address [class]
    module.add_class('Mac16Address')
    ## mac16-address.h (module 'network'): ns3::Mac16Address [class]
    root_module['ns3::Mac16Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## mac48-address.h (module 'network'): ns3::Mac48Address [class]
    module.add_class('Mac48Address')
    typehandlers.add_type_alias('void ( * ) ( ns3::Mac48Address )', 'ns3::Mac48Address::TracedCallback')
    typehandlers.add_type_alias('void ( * ) ( ns3::Mac48Address )*', 'ns3::Mac48Address::TracedCallback*')
    typehandlers.add_type_alias('void ( * ) ( ns3::Mac48Address )&', 'ns3::Mac48Address::TracedCallback&')
    ## mac48-address.h (module 'network'): ns3::Mac48Address [class]
    root_module['ns3::Mac48Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## mac64-address.h (module 'network'): ns3::Mac64Address [class]
    module.add_class('Mac64Address')
    ## mac64-address.h (module 'network'): ns3::Mac64Address [class]
    root_module['ns3::Mac64Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## mac8-address.h (module 'network'): ns3::Mac8Address [class]
    module.add_class('Mac8Address')
    ## mac8-address.h (module 'network'): ns3::Mac8Address [class]
    root_module['ns3::Mac8Address'].implicitly_converts_to(root_module['ns3::Address'])
    ## net-device-container.h (module 'network'): ns3::NetDeviceContainer [class]
    module.add_class('NetDeviceContainer')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::NetDevice > > const_iterator', 'ns3::NetDeviceContainer::Iterator')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::NetDevice > > const_iterator*', 'ns3::NetDeviceContainer::Iterator*')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::NetDevice > > const_iterator&', 'ns3::NetDeviceContainer::Iterator&')
    ## node-container.h (module 'network'): ns3::NodeContainer [class]
    module.add_class('NodeContainer')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::Node > > const_iterator', 'ns3::NodeContainer::Iterator')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::Node > > const_iterator*', 'ns3::NodeContainer::Iterator*')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::Node > > const_iterator&', 'ns3::NodeContainer::Iterator&')
    ## node-list.h (module 'network'): ns3::NodeList [class]
    module.add_class('NodeList')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::Node > > const_iterator', 'ns3::NodeList::Iterator')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::Node > > const_iterator*', 'ns3::NodeList::Iterator*')
    typehandlers.add_type_alias('std::vector< ns3::Ptr< ns3::Node > > const_iterator&', 'ns3::NodeList::Iterator&')
    ## non-copyable.h (module 'core'): ns3::NonCopyable [class]
    module.add_class('NonCopyable', import_from_module='ns.core', destructor_visibility='protected')
    ## object-base.h (module 'core'): ns3::ObjectBase [class]
    module.add_class('ObjectBase', import_from_module='ns.core', allow_subclassing=True)
    ## object.h (module 'core'): ns3::ObjectDeleter [struct]
    module.add_class('ObjectDeleter', import_from_module='ns.core')
    ## object-factory.h (module 'core'): ns3::ObjectFactory [class]
    module.add_class('ObjectFactory', import_from_module='ns.core')
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata [class]
    module.add_class('PacketMetadata')
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item [struct]
    module.add_class('Item', outer_class=root_module['ns3::PacketMetadata'])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::Item::ItemType [enumeration]
    module.add_enum('ItemType', ['PAYLOAD', 'HEADER', 'TRAILER'], outer_class=root_module['ns3::PacketMetadata::Item'])
    ## packet-metadata.h (module 'network'): ns3::PacketMetadata::ItemIterator [class]
    module.add_class('ItemIterator', outer_class=root_module['ns3::PacketMetadata'])
    ## packet-socket-address.h (module 'network'): ns3::PacketSocketAddress [class]
    module.add_class('PacketSocketAddress')
    ## packet-socket-address.h (module 'network'): ns3::PacketSocketAddress [class]
    root_module['ns3::PacketSocketAddress'].implicitly_converts_to(root_module['ns3::Address'])
    ## packet-socket-helper.h (module 'network'): ns3::PacketSocketHelper [class]
    module.add_class('PacketSocketHelper')
    ## packet.h (module 'network'): ns3::PacketTagIterator [class]
    module.add_class('PacketTagIterator')
    ## packet.h (module 'network'): ns3::PacketTagIterator::Item [class]
    module.add_class('Item', outer_class=root_module['ns3::PacketTagIterator'])
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList [class]
    module.add_class('PacketTagList')
    ## packet-tag-list.h (module 'network'): ns3::PacketTagList::TagData [struct]
    module.add_class('TagData', outer_class=root_module['ns3::PacketTagList'])
    ## log.h (module 'core'): ns3::ParameterLogger [class]
    module.add_class('ParameterLogger', import_from_module='ns.core')
    ## packetbb.h (module 'network'): ns3::PbbAddressTlvBlock [class]
    module.add_class('PbbAddressTlvBlock')
    typehandlers.add_type_alias('std::list< ns3::Ptr< ns3::PbbAddressTlv > > iterator', 'ns3::PbbAddressTlvBlock::Iterator')
    typehandlers.add_type_alias('std::list< ns3::Ptr< ns3::PbbAddressTlv > > iterator*', 'ns3::PbbAddressTlvBlock::Iterator*')
    typehandlers.add_type_alias('std::list< ns3::Ptr< ns3::PbbAddressTlv > > iterator&', 'ns3::PbbAddressTlvBlock::Iterator&')
    typehandlers.add_type_alias('std::list< ns3::Ptr< ns3::PbbAddressTlv > > const_iterator', 'ns3::PbbAddressTlvBlock::ConstIterator')
    typehandlers.add_type_alias('std::list< ns3::Ptr< ns3::PbbAddressTlv > > const_iterator*', 'ns3::PbbAddressTlvBlock::ConstIterator*')
    typehandlers.add_type_alias('std::list< ns3::Ptr< ns3::PbbAddressTlv > > const_iterator&', 'ns3::PbbAddressTlvBlock::ConstIterator&')
    ## packetbb.h (module 'network'): ns3::PbbTlvBlock [class]
    module.add_class('PbbTlvBlock')
    typehandlers.add_type_alias('std::list< ns3::Ptr< ns3::PbbTlv > > iterator', 'ns3::PbbTlvBlock::Iterator')
    typehandlers.add_type_alias('std::list< ns3::Ptr< ns3::PbbTlv > > iterator*', 'ns3::PbbTlvBlock::Iterator*')
    typehandlers.add_type_alias('std::list< ns3::Ptr< ns3::PbbTlv > > iterator&', 'ns3::PbbTlvBlock::Iterator&')
    typehandlers.add_type_alias('std::list< ns3::Ptr< ns3::PbbTlv > > const_iterator', 'ns3::PbbTlvBlock::ConstIterator')
    typehandlers.add_type_alias('std::list< ns3::Ptr< ns3::PbbTlv > > const_iterator*', 'ns3::PbbTlvBlock::ConstIterator*')
    typehandlers.add_type_alias('std::list< ns3::Ptr< ns3::PbbTlv > > const_iterator&', 'ns3::PbbTlvBlock::ConstIterator&')
    ## pcap-file.h (module 'network'): ns3::PcapFile [class]
    module.add_class('PcapFile')
    ## trace-helper.h (module 'network'): ns3::PcapHelper [class]
    module.add_class('PcapHelper')
    ## trace-helper.h (module 'network'): ns3::PcapHelper::DataLinkType [enumeration]
    module.add_enum('DataLinkType', ['DLT_NULL', 'DLT_EN10MB', 'DLT_PPP', 'DLT_RAW', 'DLT_IEEE802_11', 'DLT_LINUX_SLL', 'DLT_PRISM_HEADER', 'DLT_IEEE802_11_RADIO', 'DLT_IEEE802_15_4', 'DLT_NETLINK'], outer_class=root_module['ns3::PcapHelper'])
    ## trace-helper.h (module 'network'): ns3::PcapHelperForDevice [class]
    module.add_class('PcapHelperForDevice', allow_subclassing=True)
    ## queue-size.h (module 'network'): ns3::QueueSize [class]
    module.add_class('QueueSize')
    ## sequence-number.h (module 'network'): ns3::SequenceNumber<unsigned int, int> [class]
    module.add_class('SequenceNumber32')
    ## sequence-number.h (module 'network'): ns3::SequenceNumber<unsigned short, short> [class]
    module.add_class('SequenceNumber16')
    ## simple-net-device-helper.h (module 'network'): ns3::SimpleNetDeviceHelper [class]
    module.add_class('SimpleNetDeviceHelper')
    ## simple-ref-count.h (module 'core'): ns3::SimpleRefCount<ns3::Object, ns3::ObjectBase, ns3::ObjectDeleter> [class]
    module.add_class('SimpleRefCount', import_from_module='ns.core', memory_policy=cppclass.ReferenceCountingMethodsPolicy(incref_method='Ref', decref_method='Unref', peekref_method='GetReferenceCount'), automatic_type_narrowing=True, parent=root_module['ns3::ObjectBase'], template_parameters=['ns3::Object', 'ns3::ObjectBase', 'ns3::ObjectDeleter'])
    ## simulator.h (module 'core'): ns3::Simulator [class]
    module.add_class('Simulator', import_from_module='ns.core', destructor_visibility='private')
    ## simulator.h (module 'core'): ns3::Simulator [enumeration]
    module.add_enum('', ['NO_CONTEXT'], outer_class=root_module['ns3::Simulator'], import_from_module='ns.core')
    ## data-calculator.h (module 'stats'): ns3::StatisticalSummary [class]
    module.add_class('StatisticalSummary', import_from_module='ns.stats', allow_subclassing=True)
    ## system-wall-clock-ms.h (module 'core'): ns3::SystemWallClockMs [class]
    module.add_class('SystemWallClockMs', import_from_module='ns.core')
    ## tag.h (module 'network'): ns3::Tag [class]
    module.add_class('Tag', parent=root_module['ns3::ObjectBase'])
    ## tag-buffer.h (module 'network'): ns3::TagBuffer [class]
    module.add_class('TagBuffer')
    ## nstime.h (module 'core'): ns3::Time [class]
    module.add_class('Time', import_from_module='ns.core')
    ## nstime.h (module 'core'): ns3::Time::Unit [enumeration]
    module.add_enum('Unit', ['Y', 'D', 'H', 'MIN', 'S', 'MS', 'US', 'NS', 'PS', 'FS', 'LAST', 'AUTO'], outer_class=root_module['ns3::Time'], import_from_module='ns.core')
    typehandlers.add_type_alias('void ( * ) ( ns3::Time )', 'ns3::Time::TracedCallback')
    typehandlers.add_type_alias('void ( * ) ( ns3::Time )*', 'ns3::Time::TracedCallback*')
    typehandlers.add_type_alias('void ( * ) ( ns3::Time )&', 'ns3::Time::TracedCallback&')
    ## nstime.h (module 'core'): ns3::TimeWithUnit [class]
    module.add_class('TimeWithUnit', import_from_module='ns.core')
