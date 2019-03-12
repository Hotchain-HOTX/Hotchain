// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX Developers 
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include "pow.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"



//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}
 static bool regenerate = false;

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0xd068f8289608418e66e7beb9c2a4ba566ee90c0e56f9e4c6eb910135f6bfa98f"))
    (20, uint256("0x000002e51d8e490cddf0c50405fd4f4b82aacf370cca51aa88654f43f30ef22e"))
    (50, uint256("0x0000009f2cc7fc31c7521cf831b401e65ca766fda81727f2bd58707b18e5db29"))
    (75, uint256("0x00000069ed8ff5995d1a0aa6f1cf264d65ed1f81b3a28bb6824b825818bcb920"))
    (100, uint256("0x00000027acc7cdfe4d64cd2a18e9d31ff8790c24665e2a4cc49b9df8d511d9c6"))
    (150, uint256("0x000000282a9338e31746eb7f6f355951bd7cf7fe6ac061e32eb3c116e8ca0de2"))
    (200, uint256("0x00000036529d83e78ee89b0ff27e9b9844c3246af430095354040c575cd20b2b"))
    (250, uint256("0x6d9cfc90a07cd5771b4680bb7e842951786c26b1ad73f21682e0efb9891d6e1c"))
    (300, uint256("0x9a0faa4d2f0342d95017511a3e620775f9a2f56635ad5c59cf61d9cc1d1804e4"))
    (500, uint256("0x5fc9a775b58c444811e2183ef46defc932a13344595ec3759400bc54ae0c2048"))
    (15000, uint256("0x5fc9a775b58c444811e2183ef46defc932a13344595ec3759400bc54ae0c2048"));
	
static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1552385233, // * UNIX timestamp of last checkpoint block
    29934,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0xd068f8289608418e66e7beb9c2a4ba566ee90c0e56f9e4c6eb910135f6bfa98f"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1551486723,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0xd068f8289608418e66e7beb9c2a4ba566ee90c0e56f9e4c6eb910135f6bfa98f"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1551486723,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x48;
        pchMessageStart[1] = 0x4f;
        pchMessageStart[2] = 0x54;
        pchMessageStart[3] = 0x58;
        vAlertPubKey = ParseHex("0444c17bb301c3a3b2bf166a0815e73b0c715976df4ea972e86df1db0f58ab69bc7188661b1d53667f52d8cc9ce9e9037b7880c9ddf4bc664c7b2fbad349c9d94c");
        nP2pPort = 9069;
        nRpcPort = 6990;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Hotchain starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 8100; // 75%
        nRejectBlockOutdatedMajority = 10260; // 95%
        nToCheckBlockUpgradeMajority = 10800; // Approximate expected amount of blocks in 7 days (1440*7.5)
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Hotchain: 1 day
        nTargetSpacing = 1 * 60;  // Hotchain: 1 minute
        nMaturity = 10;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 21000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPoWBlock = 200;
        //nModifierUpdateBlock = 1;
        //nZerocoinStartHeight = 210;
        //nZerocoinStartTime = 1551486723; 
        //nBlockEnforceSerialRange = 895400; //Enforce serial range starting this block
        //nBlockRecalculateAccumulators = 908000; //Trigger a recalculation of accumulators
        //nBlockFirstFraudulent = 891737; //First block that bad serials emerged
        //nBlockLastGoodCheckpoint = 210; //Last valid accumulator checkpoint
        //nBlockEnforceInvalidUTXO = 902850; //Start enforcing the invalid UTXO's
        //nInvalidAmountFiltered = 268200*COIN; //Amount of invalid coins filtered through exchanges, that should be considered valid
        //nBlockZerocoinV2 = 210; //!> The block that zerocoin v2 becomes active - roughly Tuesday, May 8, 2018 4:00:00 AM GMT
        //nEnforceNewSporkKey = 1525158000; //!> Sporks signed after (GMT): Tuesday, May 1, 2018 7:00:00 AM GMT must use the new spork key
        //nRejectOldSporkKey = 1527811200; //!> Fully reject old spork key after (GMT): Friday, June 1, 2018 12:00:00 AM

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         */
        const char* pszTimestamp = "Il 3/2/2019 ho creato Hotchain per il sollazzo di tutti!";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c5bb83de4a978725c05fe2de5aeaf3522f87fdb10e074ccc4182b0408ac85e1278c17649171639506407e23bf3614a7ad464eed7d5c54ebfd3cb068db77622cb") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 4;
        genesis.nAccumulatorCheckpoint = 0;
        genesis.nTime = 1551486723;
        genesis.nBits = 504365040;
        genesis.nNonce = 80512;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                while (genesis.GetHash() > bnProofOfWorkLimit)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Mainnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";
            }
        } else {
            assert(hashGenesisBlock == uint256("0xd068f8289608418e66e7beb9c2a4ba566ee90c0e56f9e4c6eb910135f6bfa98f"));
            assert(genesis.hashMerkleRoot == uint256("0x5d68db3baf3175ec87588e5dce18cdad7b2fc568b7303b27b10b068915742ce7"));
        }


	vSeeds.push_back(CDNSSeedData("node-01.hotchain.me", "node-01.hotchain.me"));
        vSeeds.push_back(CDNSSeedData("node-02.hotchain.me", "node-02.hotchain.me"));
        vSeeds.push_back(CDNSSeedData("node-03.hotchain.me", "node-03.hotchain.me"));
        vSeeds.push_back(CDNSSeedData("node-04.hotchain.me", "node-04.hotchain.me"));
        vSeeds.push_back(CDNSSeedData("node-05.hotchain.me", "node-05.hotchain.me"));
        vSeeds.push_back(CDNSSeedData("node-06.hotchain.me", "node-06.hotchain.me"));
        vSeeds.push_back(CDNSSeedData("node-07.hotchain.me", "node-07.hotchain.me"));
        vSeeds.push_back(CDNSSeedData("node-08.hotchain.me", "node-08.hotchain.me"));
        vSeeds.push_back(CDNSSeedData("node-09.hotchain.me", "node-09.hotchain.me"));
        vSeeds.push_back(CDNSSeedData("node-10.hotchain.me", "node-10.hotchain.me"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 100); // Hotchain's wallet address starts with a h
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 40); // 7
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 40); // 7
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x72)(0x79)(0x84).convert_to_container<std::vector<unsigned char> >();

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = true;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "047c3db4661b777f31ceb1d61a9d8aa8035410e2134d01b6291966fe062e7abc207efe7d51019e20fd7809da1b306cc2040b44e60f65b7047cd4573a985328c946";
        strObfuscationPoolDummyAddress = "hWQhYziqvYbRW6iutAeChDkjajNbevHgmh";

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zhotx to be stakable
        nStakeMinAge = 60 * 60; //The number of seconds that a utxo must be old before it can qualify for staking
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x4c;
        pchMessageStart[1] = 0x7e;
        pchMessageStart[2] = 0xe5;
        pchMessageStart[3] = 0xd4;
        vAlertPubKey = ParseHex("04c6714cd6fe2de4d5757b391785a7459cc50650612198f5ab96fa2b33dbf476a950d4ac2b51718fd75e0da32ac61d67bba4a63c0bea415e704a8f505043815fad");
        nP2pPort = 19069;
        nRpcPort = 16990;
        nEnforceBlockUpgradeMajority = 4320; // 75%
        nRejectBlockOutdatedMajority = 5472; // 95%
        nToCheckBlockUpgradeMajority = 5760; // 4 days
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Hotchain: 1 day
        nTargetSpacing = 1 * 60;  // Hotchain: 1 minute
        nLastPoWBlock = 200;
        nMaturity = 10;
        nMaxMoneyOut = 21000000 * COIN;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1551486723;
        genesis.nNonce = 80512;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                while (genesis.GetHash() > bnProofOfWorkLimit)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Testnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            assert(hashGenesisBlock == uint256("0xd068f8289608418e66e7beb9c2a4ba566ee90c0e56f9e4c6eb910135f6bfa98f"));
            assert(genesis.hashMerkleRoot == uint256("0x5d68db3baf3175ec87588e5dce18cdad7b2fc568b7303b27b10b068915742ce7"));
        }

        vSeeds.clear();
         vSeeds.push_back(CDNSSeedData("tnseeder-01.Hotchain.io", "tnseeder-01.Hotchain.io"));
         vSeeds.push_back(CDNSSeedData("testnode-01.Hotchain.io", "testnode-01.Hotchain.io"));
         vSeeds.push_back(CDNSSeedData("testnode-02.Hotchain.io", "testnode-02.Hotchain.io"));
         vSeeds.push_back(CDNSSeedData("testnode-03.Hotchain.io", "testnode-03.Hotchain.io"));
         vSeeds.push_back(CDNSSeedData("testnode-04.Hotchain.io", "testnode-04.Hotchain.io"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 17); // Testnet Hotchain addresses start with '7'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 18);  // Testnet Hotchain script addresses start with '8'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 65);     // Testnet private keys start with 'T'
        // Testnet Hotchain BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet Hotchain BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet Hotchain BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04b3db0f8006d1291765fed004d848a8581b192e948f2761d3f56244a78b66ad52b08839054e0703e894afcac701cbc848dc7e30384d145a71131518d3f4939058";
        strObfuscationPoolDummyAddress = "y57cqfGRkekRyDRNeJiLtYVEbvhXrNbmox";
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Hotchain: 1 day
        nTargetSpacing = 1 * 60;        // Hotchain: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1551486723;
        genesis.nBits = 504365040;
        genesis.nNonce = 80512;
        nP2pPort = 51476;

        hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                while (genesis.GetHash() > bnProofOfWorkLimit)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Regtest ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            assert(hashGenesisBlock == uint256("0xd068f8289608418e66e7beb9c2a4ba566ee90c0e56f9e4c6eb910135f6bfa98f"));
            assert(genesis.hashMerkleRoot == uint256("0x5d68db3baf3175ec87588e5dce18cdad7b2fc568b7303b27b10b068915742ce7"));
        }
        if (regenerate)
            exit(0);

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nP2pPort = 51478;
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
