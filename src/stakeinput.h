// Copyright (c) 2017-2018 The PIVX Developers
// Copyright (c) 2018 The HOTCHAIN Developers 
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HOTCHAIN_STAKEINPUT_H
#define HOTCHAIN_STAKEINPUT_H

class CKeyStore;
class CWallet;
class CWalletTx;

class CStakeInput
{
protected:
    CBlockIndex* pindexFrom;

public:
    virtual ~CStakeInput(){};
    virtual CBlockIndex* GetIndexFrom() = 0;
    virtual bool CreateTxIn(CWallet* pwallet, CTxIn& txIn, uint256 hashTxOut = 0) = 0;
    virtual bool GetTxFrom(CTransaction& tx) = 0;
    virtual CAmount GetValue() = 0;
    virtual bool CreateTxOuts(CWallet* pwallet, vector<CTxOut>& vout, CAmount nTotal) = 0;
    virtual bool GetModifier(uint64_t& nStakeModifier) = 0;
    virtual bool IszHOTX() = 0;
    virtual CDataStream GetUniqueness() = 0;
};


// zHOTXStake can take two forms
// 1) the stake candidate, which is a zcmint that is attempted to be staked
// 2) a staked zhotx, which is a zcspend that has successfully staked
class CzHotxStake : public CStakeInput
{
private:
    uint32_t nChecksum;
    bool fMint;
    libzerocoin::CoinDenomination denom;
    uint256 hashSerial;

public:
    explicit CzHotxStake(libzerocoin::CoinDenomination denom, const uint256& hashSerial)
    {
        this->denom = denom;
        this->hashSerial = hashSerial;
        this->pindexFrom = nullptr;
        fMint = true;
    }

    explicit CzHotxStake(const libzerocoin::CoinSpend& spend);

    CBlockIndex* GetIndexFrom() override;
    bool GetTxFrom(CTransaction& tx) override;
    CAmount GetValue() override;
    bool GetModifier(uint64_t& nStakeModifier) override;
    CDataStream GetUniqueness() override;
    bool CreateTxIn(CWallet* pwallet, CTxIn& txIn, uint256 hashTxOut = 0) override;
    bool CreateTxOuts(CWallet* pwallet, vector<CTxOut>& vout, CAmount nTotal) override;
    bool MarkSpent(CWallet* pwallet, const uint256& txid);
    bool IszHOTX() override { return true; }
    int GetChecksumHeightFromMint();
    int GetChecksumHeightFromSpend();
    uint32_t GetChecksum();
};

class CHotxStake : public CStakeInput
{
private:
    CTransaction txFrom;
    unsigned int nPosition;
public:
    CHotxStake()
    {
        this->pindexFrom = nullptr;
    }

    bool SetInput(CTransaction txPrev, unsigned int n);

    CBlockIndex* GetIndexFrom() override;
    bool GetTxFrom(CTransaction& tx) override;
    CAmount GetValue() override;
    bool GetModifier(uint64_t& nStakeModifier) override;
    CDataStream GetUniqueness() override;
    bool CreateTxIn(CWallet* pwallet, CTxIn& txIn, uint256 hashTxOut = 0) override;
    bool CreateTxOuts(CWallet* pwallet, vector<CTxOut>& vout, CAmount nTotal) override;
    bool IszHOTX() override { return false; }
};


#endif //HOTCHAIN_STAKEINPUT_H
