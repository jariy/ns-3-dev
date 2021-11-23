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
    root_module = Module('ns.wifi', cpp_namespace='::ns3')
    return root_module

def register_types(module):
    root_module = module.get_root()
    
    ## propagation-environment.h (module 'propagation'): ns3::EnvironmentType [enumeration]
    module.add_enum('EnvironmentType', ['UrbanEnvironment', 'SubUrbanEnvironment', 'OpenAreasEnvironment'], import_from_module='ns.propagation')
    ## propagation-environment.h (module 'propagation'): ns3::CitySize [enumeration]
    module.add_enum('CitySize', ['SmallCity', 'MediumCity', 'LargeCity'], import_from_module='ns.propagation')
    ## queue-size.h (module 'network'): ns3::QueueSizeUnit [enumeration]
    module.add_enum('QueueSizeUnit', ['PACKETS', 'BYTES'], import_from_module='ns.network')
    ## wifi-phy.h (module 'wifi'): ns3::WifiPhyRxfailureReason [enumeration]
    module.add_enum('WifiPhyRxfailureReason', ['UNKNOWN', 'UNSUPPORTED_SETTINGS', 'CHANNEL_SWITCHING', 'RXING', 'TXING', 'SLEEPING', 'BUSY_DECODING_PREAMBLE', 'PREAMBLE_DETECT_FAILURE', 'RECEPTION_ABORTED_BY_TX', 'L_SIG_FAILURE', 'SIG_A_FAILURE', 'PREAMBLE_DETECTION_PACKET_SWITCH', 'FRAME_CAPTURE_PACKET_SWITCH', 'OBSS_PD_CCA_RESET', 'FILTERED'])
    ## wifi-mpdu-type.h (module 'wifi'): ns3::MpduType [enumeration]
    module.add_enum('MpduType', ['NORMAL_MPDU', 'SINGLE_MPDU', 'FIRST_MPDU_IN_AGGREGATE', 'MIDDLE_MPDU_IN_AGGREGATE', 'LAST_MPDU_IN_AGGREGATE'])
    ## ht-operation.h (module 'wifi'): ns3::HtProtectionType [enumeration]
    module.add_enum('HtProtectionType', ['NO_PROTECTION', 'NON_MEMBER_PROTECTION', 'TWENTY_MHZ_PROTECTION', 'MIXED_MODE_PROTECTION'])
    ## qos-txop.h (module 'wifi'): ns3::TypeOfStation [enumeration]
    module.add_enum('TypeOfStation', ['STA', 'AP', 'ADHOC_STA', 'MESH', 'HT_STA', 'HT_AP', 'HT_ADHOC_STA', 'OCB'])
    ## wifi-mac-header.h (module 'wifi'): ns3::WifiMacType [enumeration]
    module.add_enum('WifiMacType', ['WIFI_MAC_CTL_CTLWRAPPER', 'WIFI_MAC_CTL_RTS', 'WIFI_MAC_CTL_CTS', 'WIFI_MAC_CTL_ACK', 'WIFI_MAC_CTL_BACKREQ', 'WIFI_MAC_CTL_BACKRESP', 'WIFI_MAC_CTL_END', 'WIFI_MAC_CTL_END_ACK', 'WIFI_MAC_MGT_BEACON', 'WIFI_MAC_MGT_ASSOCIATION_REQUEST', 'WIFI_MAC_MGT_ASSOCIATION_RESPONSE', 'WIFI_MAC_MGT_DISASSOCIATION', 'WIFI_MAC_MGT_REASSOCIATION_REQUEST', 'WIFI_MAC_MGT_REASSOCIATION_RESPONSE', 'WIFI_MAC_MGT_PROBE_REQUEST', 'WIFI_MAC_MGT_PROBE_RESPONSE', 'WIFI_MAC_MGT_AUTHENTICATION', 'WIFI_MAC_MGT_DEAUTHENTICATION', 'WIFI_MAC_MGT_ACTION', 'WIFI_MAC_MGT_ACTION_NO_ACK', 'WIFI_MAC_MGT_MULTIHOP_ACTION', 'WIFI_MAC_DATA', 'WIFI_MAC_DATA_CFACK', 'WIFI_MAC_DATA_CFPOLL', 'WIFI_MAC_DATA_CFACK_CFPOLL', 'WIFI_MAC_DATA_NULL', 'WIFI_MAC_DATA_NULL_CFACK', 'WIFI_MAC_DATA_NULL_CFPOLL', 'WIFI_MAC_DATA_NULL_CFACK_CFPOLL', 'WIFI_MAC_QOSDATA', 'WIFI_MAC_QOSDATA_CFACK', 'WIFI_MAC_QOSDATA_CFPOLL', 'WIFI_MAC_QOSDATA_CFACK_CFPOLL', 'WIFI_MAC_QOSDATA_NULL', 'WIFI_MAC_QOSDATA_NULL_CFPOLL', 'WIFI_MAC_QOSDATA_NULL_CFACK_CFPOLL'])
    ## wifi-standards.h (module 'wifi'): ns3::WifiPhyStandard [enumeration]
    module.add_enum('WifiPhyStandard', ['WIFI_PHY_STANDARD_80211a', 'WIFI_PHY_STANDARD_80211b', 'WIFI_PHY_STANDARD_80211g', 'WIFI_PHY_STANDARD_80211_10MHZ', 'WIFI_PHY_STANDARD_80211_5MHZ', 'WIFI_PHY_STANDARD_80211p', 'WIFI_PHY_STANDARD_holland', 'WIFI_PHY_STANDARD_80211n_2_4GHZ', 'WIFI_PHY_STANDARD_80211n_5GHZ', 'WIFI_PHY_STANDARD_80211n', 'WIFI_PHY_STANDARD_80211ac', 'WIFI_PHY_STANDARD_80211ax', 'WIFI_PHY_STANDARD_UNSPECIFIED'])
    ## wifi-standards.h (module 'wifi'): ns3::WifiMacStandard [enumeration]
    module.add_enum('WifiMacStandard', ['WIFI_MAC_STANDARD_80211', 'WIFI_MAC_STANDARD_80211n', 'WIFI_MAC_STANDARD_80211ac', 'WIFI_MAC_STANDARD_80211ax'])
    ## wifi-standards.h (module 'wifi'): ns3::WifiStandard [enumeration]
    module.add_enum('WifiStandard', ['WIFI_STANDARD_80211a', 'WIFI_STANDARD_80211b', 'WIFI_STANDARD_80211g', 'WIFI_STANDARD_80211p', 'WIFI_STANDARD_holland', 'WIFI_STANDARD_80211n_2_4GHZ', 'WIFI_STANDARD_80211n_5GHZ', 'WIFI_STANDARD_80211ac', 'WIFI_STANDARD_80211ax_2_4GHZ', 'WIFI_STANDARD_80211ax_5GHZ', 'WIFI_STANDARD_80211ax_6GHZ'])
    ## wifi-phy-band.h (module 'wifi'): ns3::WifiPhyBand [enumeration]
    module.add_enum('WifiPhyBand', ['WIFI_PHY_BAND_2_4GHZ', 'WIFI_PHY_BAND_5GHZ', 'WIFI_PHY_BAND_6GHZ', 'WIFI_PHY_BAND_UNSPECIFIED'])
    ## qos-utils.h (module 'wifi'): ns3::AcIndex [enumeration]
    module.add_enum('AcIndex', ['AC_BE', 'AC_BK', 'AC_VI', 'AC_VO', 'AC_BE_NQOS', 'AC_UNDEF'])
    ## wifi-preamble.h (module 'wifi'): ns3::WifiPreamble [enumeration]
    module.add_enum('WifiPreamble', ['WIFI_PREAMBLE_LONG', 'WIFI_PREAMBLE_SHORT', 'WIFI_PREAMBLE_HT_MF', 'WIFI_PREAMBLE_HT_GF', 'WIFI_PREAMBLE_VHT_SU', 'WIFI_PREAMBLE_VHT_MU', 'WIFI_PREAMBLE_HE_SU', 'WIFI_PREAMBLE_HE_ER_SU', 'WIFI_PREAMBLE_HE_MU', 'WIFI_PREAMBLE_HE_TB'])
    ## block-ack-type.h (module 'wifi'): ns3::BlockAckType [enumeration]
    module.add_enum('BlockAckType', ['BASIC_BLOCK_ACK', 'COMPRESSED_BLOCK_ACK', 'EXTENDED_COMPRESSED_BLOCK_ACK', 'MULTI_TID_BLOCK_ACK'])
    ## wifi-mode.h (module 'wifi'): ns3::WifiModulationClass [enumeration]
    module.add_enum('WifiModulationClass', ['WIFI_MOD_CLASS_UNKNOWN', 'WIFI_MOD_CLASS_IR', 'WIFI_MOD_CLASS_FHSS', 'WIFI_MOD_CLASS_DSSS', 'WIFI_MOD_CLASS_HR_DSSS', 'WIFI_MOD_CLASS_ERP_PBCC', 'WIFI_MOD_CLASS_DSSS_OFDM', 'WIFI_MOD_CLASS_ERP_OFDM', 'WIFI_MOD_CLASS_OFDM', 'WIFI_MOD_CLASS_HT', 'WIFI_MOD_CLASS_VHT', 'WIFI_MOD_CLASS_HE'])
    ## wifi-mode.h (module 'wifi'): ns3::WifiCodeRate [enumeration]
    module.add_enum('WifiCodeRate', ['WIFI_CODE_RATE_UNDEFINED', 'WIFI_CODE_RATE_3_4', 'WIFI_CODE_RATE_2_3', 'WIFI_CODE_RATE_1_2', 'WIFI_CODE_RATE_5_6'])
    ## log.h (module 'core'): ns3::LogLevel [enumeration]
    module.add_enum('LogLevel', ['LOG_NONE', 'LOG_ERROR', 'LOG_LEVEL_ERROR', 'LOG_WARN', 'LOG_LEVEL_WARN', 'LOG_DEBUG', 'LOG_LEVEL_DEBUG', 'LOG_INFO', 'LOG_LEVEL_INFO', 'LOG_FUNCTION', 'LOG_LEVEL_FUNCTION', 'LOG_LOGIC', 'LOG_LEVEL_LOGIC', 'LOG_ALL', 'LOG_LEVEL_ALL', 'LOG_PREFIX_FUNC', 'LOG_PREFIX_TIME', 'LOG_PREFIX_NODE', 'LOG_PREFIX_LEVEL', 'LOG_PREFIX_ALL'], import_from_module='ns.core')
    ## address.h (module 'network'): ns3::Address [class]
    module.add_class('Address', import_from_module='ns.network')
    ## address.h (module 'network'): ns3::Address::MaxSize_e [enumeration]
    module.add_enum('MaxSize_e', ['MAX_SIZE'], outer_class=root_module['ns3::Address'], import_from_module='ns.network')
    ## angles.h (module 'antenna'): ns3::Angles [struct]
    module.add_class('Angles', import_from_module='ns.antenna')
    ## sta-wifi-mac.h (module 'wifi'): ns3::ApInfo [struct]
    module.add_class('ApInfo')
    ## trace-helper.h (module 'network'): ns3::AsciiTraceHelper [class]
    module.add_class('AsciiTraceHelper', import_from_module='ns.network')
    ## trace-helper.h (module 'network'): ns3::AsciiTraceHelperForDevice [class]
    module.add_class('AsciiTraceHelperForDevice', import_from_module='ns.network', allow_subclassing=True)
    ## athstats-helper.h (module 'wifi'): ns3::AthstatsHelper [class]
    module.add_class('AthstatsHelper')
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList [class]
    module.add_class('AttributeConstructionList', import_from_module='ns.core')
    ## attribute-construction-list.h (module 'core'): ns3::AttributeConstructionList::Item [struct]
    module.add_class('Item', import_from_module='ns.core', outer_class=root_module['ns3::AttributeConstructionList'])
    typehandlers.add_type_alias('std::list< ns3::AttributeConstructionList::Item > const_iterator', 'ns3::AttributeConstructionList::CIterator')
    typehandlers.add_type_alias('std::list< ns3::AttributeConstructionList::Item > const_iterator*', 'ns3::AttributeConstructionList::CIterator*')
    typehandlers.add_type_alias('std::list< ns3::AttributeConstructionList::Item > const_iterator&', 'ns3::AttributeConstructionList::CIterator&')
    ## spectrum-model.h (module 'spectrum'): ns3::BandInfo [struct]
    module.add_class('BandInfo', import_from_module='ns.spectrum')
    ## block-ack-manager.h (module 'wifi'): ns3::Bar [struct]
    module.add_class('Bar')
    ## block-ack-agreement.h (module 'wifi'): ns3::BlockAckAgreement [class]
    module.add_class('BlockAckAgreement')
    ## block-ack-cache.h (module 'wifi'): ns3::BlockAckCache [class]
    module.add_class('BlockAckCache')
    ## block-ack-window.h (module 'wifi'): ns3::BlockAckWindow [class]
    module.add_class('BlockAckWindow')
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
