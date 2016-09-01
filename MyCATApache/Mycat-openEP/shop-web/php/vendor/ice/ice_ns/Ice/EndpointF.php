<?php
// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.5.1
//
// <auto-generated>
//
// Generated from file `EndpointF.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//


namespace Ice
{
    if(!isset($Ice__t_EndpointInfo))
    {
        $Ice__t_EndpointInfo = IcePHP_declareClass('::Ice::EndpointInfo');
    }
}

namespace Ice
{
    if(!isset($Ice__t_TCPEndpointInfo))
    {
        $Ice__t_TCPEndpointInfo = IcePHP_declareClass('::Ice::TCPEndpointInfo');
    }
}

namespace Ice
{
    if(!isset($Ice__t_UDPEndpointInfo))
    {
        $Ice__t_UDPEndpointInfo = IcePHP_declareClass('::Ice::UDPEndpointInfo');
    }
}

namespace Ice
{
    if(!isset($Ice__t_Endpoint))
    {
        $Ice__t_Endpoint = IcePHP_declareClass('::Ice::Endpoint');
    }
}

namespace Ice
{
    if(!isset($Ice__t_EndpointSeq))
    {
        $Ice__t_EndpointSeq = IcePHP_defineSequence('::Ice::EndpointSeq', $Ice__t_Endpoint);
    }
}
?>