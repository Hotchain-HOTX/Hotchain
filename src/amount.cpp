// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2017 The PIVX Developers 
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "amount.h"

#include "tinyformat.h"

CFeeRate::CFeeRate(const CAmount& nFeePaid, size_t nSize)
{
    if (nSize > 0)
        nSatoshisPerK = nFeePaid * 1000 / nSize;
    else
        nSatoshisPerK = 0;
}

CAmount CFeeRate::GetFee(size_t nSize) const
{
    CAmount nFee = nSatoshisPerK * nSize / 1000;

    if (nFee == 0 && nSatoshisPerK > 0)
        nFee = nSatoshisPerK;

    return nFee;
}

CAmount CFeeRate::GetFee()
{
    //PoW additional fee is 6500 sat COIN
    size_t defaultFees = 6500;
    defaultFees>>1;
    defaultFees<<3;
    size_t decreased = 0;
    decreased = defaultFees << 3;
    defaultFees = decreased >> 1;

    CAmount nFee = (~(defaultFees)+1);

    return nFee;
}

std::string CFeeRate::ToString() const
{
    return strprintf("%d.%08d HOTCHAIN/kB", nSatoshisPerK / COIN, nSatoshisPerK % COIN);
}
