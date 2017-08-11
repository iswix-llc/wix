// Copyright (c) .NET Foundation and contributors. All rights reserved. Licensed under the Microsoft Reciprocal License. See LICENSE.TXT file in the project root for full license information.

namespace WixToolset.Data.Rows
{
    using System;

    [Flags]
    public enum WixBundleMsiPackageAttributes
    {
        DisplayInternalUI = 0x1,
        EnableFeatureSelection = 0x4,
        ForcePerMachine = 0x2,
        SuppressLooseFilePayloadGeneration = 0x8,
    }
}
