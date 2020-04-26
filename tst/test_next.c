/**
 * @file
 *
 * Test suite of LibISAAC
 *
 * @copyright Copyright © 2020, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 * @license BSD 3-clause license.
 */

#include "test.h"

#define EXPECTED_NEXT_ELEMENTS 512

/*
 * This is the stream of uint32 values obtained by calling isaac_next()
 * repeatedly after the isaac_ctx_t has been initialised with a zero seed.
 *
 * The value is obtained by taking the original ISAAC implementation
 * (in particular `randport.c`), zero-initialising the seed
 * and calling `rand(&ctx)` repeatedly.
 *
 *     randctx ctx;
 *     unsigned long int i;
 *     unsigned long int next;
 *     for (i = 0; i < 256; i++) {
 *         ctx.randrsl[i] = 0;  // Zero seed
 *     }
 *     randinit(&ctx, TRUE); // Init ISAAC with zero seed
 *     for (i = 0; i < 512; i++) {
 *          next = rand(&ctx);
 *          printf("0x%08lXUL, ", next);
 *     }
 */
const static uint32_t expected_next_results[EXPECTED_NEXT_ELEMENTS] = {
        0x182600F3UL, 0x300B4A8DUL, 0x301B6622UL, 0xB08ACD21UL, 0x296FD679UL,
        0x995206E9UL, 0xB3FFA8B5UL, 0x0FC99C24UL, 0x5F071FAFUL, 0x52251DEFUL,
        0x894F41C2UL, 0xCC4C9AFBUL, 0x96C33F74UL, 0x347CB71DUL, 0xC90F8FBDUL,
        0xA658F57AUL, 0xC5C29E18UL, 0x6249FA29UL, 0xBAE16FFAUL, 0x25C871BDUL,
        0xF4C75E24UL, 0x5AB3EAB9UL, 0xAC450B8FUL, 0x1629CFA4UL, 0x0016E86FUL,
        0xF27C4D0DUL, 0x67648B17UL, 0x05C04FCEUL, 0x44D3FF79UL, 0xC6ACD20FUL,
        0x472FD994UL, 0x842131C4UL, 0xEAD4A900UL, 0xC01EDA0DUL, 0x9E604C7BUL,
        0xFB8A0E99UL, 0x02E17B6FUL, 0xE8B4F627UL, 0xC7041EAEUL, 0x42D19CD7UL,
        0xA358EB94UL, 0x19CA2158UL, 0x6BE6CE81UL, 0x4B90A4DEUL, 0x26F0774DUL,
        0x4E83930AUL, 0x2492D476UL, 0xB97FFABEUL, 0x675CC8AEUL, 0x4CFDD254UL,
        0x5D3C00EAUL, 0x7BBA5EADUL, 0x6F461810UL, 0xBEF63EEAUL, 0x72EB767BUL,
        0xED6E963BUL, 0xB026016DUL, 0x17CB7EBFUL, 0xA7DC6E56UL, 0xF460BDF1UL,
        0x1FFE0E04UL, 0x902B347DUL, 0x02C0D8ABUL, 0x98CB3F8BUL, 0x6F359A39UL,
        0x9521825FUL, 0x9026D97EUL, 0xDE342516UL, 0x890A740CUL, 0x0F2969E4UL,
        0x2E7EA9EDUL, 0x394B8A4FUL, 0x1BDF1FD0UL, 0x15D565B4UL, 0xBAF0406DUL,
        0x4DAC20DBUL, 0x03359832UL, 0xE34802D5UL, 0xCC5FFF02UL, 0x0935AD6EUL,
        0x7C53C9B2UL, 0xB10B5D29UL, 0x4FBB94BEUL, 0xD7E48546UL, 0xB7CFA23CUL,
        0x7F081C9AUL, 0xE099BAF1UL, 0x9C7DC323UL, 0xB831AD14UL, 0x5B563101UL,
        0xFA55319BUL, 0x060DED54UL, 0xC5418124UL, 0x765F0DBAUL, 0x1AD3D9D5UL,
        0x3F07EC49UL, 0xDD5E06C6UL, 0xC230E2ACUL, 0xC6BA1971UL, 0x9CC17BCCUL,
        0x10B22A22UL, 0x7DFC8C7FUL, 0xB3310333UL, 0x205530EEUL, 0xDBF38A8FUL,
        0x003A02F5UL, 0x007E96A3UL, 0x36658201UL, 0x08DFD64FUL, 0x6275ACF3UL,
        0x3D29669BUL, 0x6B2F4538UL, 0xB0CC336BUL, 0x1D3043EBUL, 0x1AD1D764UL,
        0x4C655B84UL, 0x7A725BB2UL, 0xB3FC5C66UL, 0x80B4B915UL, 0xB2CBD9E4UL,
        0x2992DFC6UL, 0xDF8BE548UL, 0xB310D06EUL, 0x436385C6UL, 0x44D6E893UL,
        0x44C4D79DUL, 0xE3BB2064UL, 0xE41EA465UL, 0x3FF4CC70UL, 0x9D21AC42UL,
        0x672C3725UL, 0xA43A1D02UL, 0xFD84B19BUL, 0x5B6FB132UL, 0x4AF40896UL,
        0xE15000A6UL, 0x7CAB12F6UL, 0x8B8E753CUL, 0xFB253454UL, 0x359AC366UL,
        0x67822B45UL, 0x290A1140UL, 0xADE6E428UL, 0x6095EFCBUL, 0x99D8D9E6UL,
        0xA5B5981DUL, 0x332C95D6UL, 0xAF5CFCABUL, 0x161F5CA6UL, 0x1844CEE2UL,
        0xFFB8AB5CUL, 0x82FCCAEBUL, 0x49ECF97AUL, 0x7A60FABDUL, 0xF9585A3AUL,
        0x4EB6BD32UL, 0x3B347002UL, 0xF4930DBAUL, 0x5D21D51EUL, 0x64E8E3F4UL,
        0x52801FA8UL, 0x71CE907CUL, 0x872783A4UL, 0x0761DC80UL, 0x5C509848UL,
        0x41BA2ADCUL, 0x7E2F5520UL, 0x85C5EEC2UL, 0x368D3D00UL, 0x5FC7C5F3UL,
        0xB849D785UL, 0xD95F25B3UL, 0x79801FD5UL, 0xBF2443D6UL, 0x360D41CDUL,
        0x651B11C0UL, 0x801A89CAUL, 0x8B9E6B94UL, 0xFDE283C4UL, 0xCC5E6974UL,
        0x2B2F4C09UL, 0x8B2160A8UL, 0xDBF57F01UL, 0x76AA1C4EUL, 0x11F0831AUL,
        0x54713D17UL, 0xC99A2639UL, 0x4C373E7AUL, 0x09E6E57FUL, 0x71F63B07UL,
        0x7BE3F02EUL, 0x2C907ADEUL, 0xE5F489F6UL, 0x0B0CD6DAUL, 0xB566E14CUL,
        0x0F955969UL, 0xA0E5710BUL, 0x80D8C2DEUL, 0x9971E496UL, 0xC7EFBC2FUL,
        0x97A48E53UL, 0x2D845C0DUL, 0xE1194B0EUL, 0xAD2BA480UL, 0xD5253552UL,
        0xCA890B31UL, 0x60060AFBUL, 0x89DAE927UL, 0x565E2229UL, 0x43ABC21CUL,
        0x03DD14A5UL, 0xBBADD184UL, 0x9E979702UL, 0x2F659883UL, 0xF313ADECUL,
        0x621BD7CAUL, 0xB6470834UL, 0x4C3901C6UL, 0x32028BB8UL, 0x9DED8244UL,
        0x66907654UL, 0x0A06B272UL, 0x4A8EC630UL, 0x4207D36FUL, 0x3E7A8B49UL,
        0x13871BE7UL, 0xBF7AF48EUL, 0x3DE0DF39UL, 0x0E864542UL, 0x8C090A23UL,
        0xAF90E49EUL, 0x97661C5EUL, 0x365AA66CUL, 0x0073E342UL, 0x9C8AC447UL,
        0x6F57E7CEUL, 0xD5BE7FFAUL, 0x89651D84UL, 0x53F78EAAUL, 0x8173DC04UL,
        0xD70B1E10UL, 0x43C1A57BUL, 0x10C8A5ABUL, 0xED6ABD62UL, 0x2F840E43UL,
        0x4873D91EUL, 0x49F413FCUL, 0x5D89A1C1UL, 0xD3A388FCUL, 0x96C59CF4UL,
        0x456F1EDDUL, 0x3DD20023UL, 0xA264E933UL, 0xD32956E5UL, 0xD91AA738UL,
        0xE76DD339UL, 0x7A68710FUL, 0x6554ABDAUL, 0x90C10757UL, 0x0B5E435FUL,
        0xAF7D1FB8UL, 0x01913FD3UL, 0x6A158D10UL, 0xB8F6FD4AUL, 0xC2B9AA36UL,
        0x96DA2655UL, 0xFE1E42D5UL, 0x56E6CD21UL, 0xD5B2D750UL, 0x7229EA81UL,
        0x5DE87ABBUL, 0xB6B9D766UL, 0x1E16614CUL, 0x3B708F99UL, 0x5CF824CDUL,
        0xA4CA0CF1UL, 0x62D31911UL, 0x7CDD662FUL, 0xCB9E1563UL, 0x79AE4C10UL,
        0x080C79ECUL, 0x18080C8EUL, 0x4A0A283CUL, 0x3DDE9F39UL, 0x09C36F90UL,
        0xAD567643UL, 0x08294766UL, 0xB4415F7DUL, 0x5597EC0FUL, 0x78FFA568UL,
        0x8BACE62EUL, 0x4188BFCDUL, 0xC87C8006UL, 0xAFA92A6DUL, 0x50FC8194UL,
        0xCAE8DEBAUL, 0x33F6D7B1UL, 0x53245B79UL, 0x61119A5AUL, 0x7E315AEBUL,
        0xE75B41C9UL, 0xD2A93B51UL, 0xEC46B0B6UL, 0x1ED3FF4EUL, 0x5D023E65UL,
        0xADF6BC23UL, 0xF7F58F7BUL, 0xE4F3A26AUL, 0x0C571A7DUL, 0xED35E5EEUL,
        0xEADEBEACUL, 0x30BCC764UL, 0x66F1E0ABUL, 0x826DFA89UL, 0x0D9C7E7EUL,
        0xE7E26581UL, 0xD5990DFBUL, 0x02C9B944UL, 0x4112D96CUL, 0x3FF1E524UL,
        0xC35E4580UL, 0xFDFEF62DUL, 0xB83F957AUL, 0xBFC7F7CCUL, 0xB510CE0EUL,
        0xCD7411A7UL, 0x04DB4E13UL, 0x76904B6DUL, 0x08607F04UL, 0x3718D597UL,
        0x46C0A6F5UL, 0x8406B137UL, 0x309BFB78UL, 0xF7D3F39FUL, 0x8C2F0D55UL,
        0xC613F157UL, 0x127DD430UL, 0x72C9137DUL, 0x68A39358UL, 0x07C28CD1UL,
        0x848F520AUL, 0xDD2DC1D5UL, 0x9388B13BUL, 0x28E7CB78UL, 0x03FB88F4UL,
        0xB0B84E7BUL, 0x14C8009BUL, 0x884D6825UL, 0x21C171ECUL, 0x0809E494UL,
        0x6A107589UL, 0x12595A19UL, 0x0BB3263FUL, 0x4D8FAE82UL, 0x2A98121AUL,
        0xB00960BAUL, 0x6708A2BCUL, 0x35A124B5UL, 0xBCCAAEEDUL, 0x294D37E5UL,
        0xD405DED8UL, 0x9F39E2D9UL, 0x21835C4DUL, 0xE89B1A3BUL, 0x7364944BUL,
        0xBD2E5024UL, 0x6A123F57UL, 0x34105A8CUL, 0x5AD0D3B0UL, 0xCC033CE3UL,
        0xD51F093DUL, 0x56A001E3UL, 0x01A9BD70UL, 0x8891B3DBUL, 0x13ADD922UL,
        0x3D77D9A2UL, 0x0E7E0E67UL, 0xD73F72D4UL, 0x917BDEC2UL, 0xA37F63FFUL,
        0x23D74F4EUL, 0x3A6CE389UL, 0x0606CF9FUL, 0xDE11ED34UL, 0x70CC94AEUL,
        0xCB0EEE4AUL, 0x13EDC0CBUL, 0xFE29661CUL, 0xDB6DBE96UL, 0xB388D96CUL,
        0x33BC405DUL, 0xA6D12101UL, 0x2F36FA86UL, 0x7DED386FUL, 0xE6344451UL,
        0xCD57C7F7UL, 0x1B0DCDC1UL, 0xCD49EBDBUL, 0x9E8A51DAUL, 0x12A0594BUL,
        0x60D4D5F8UL, 0x91C8D925UL, 0xE43D0FBBUL, 0x5D2A542FUL, 0x451E7EC8UL,
        0x2B36505CUL, 0x37C0ED05UL, 0x2364A1AAUL, 0x814BC24CUL, 0xE3A662D9UL,
        0xF2B5CC05UL, 0xB8B0CCFCUL, 0xB058BAFBUL, 0x3AEA3DECUL, 0x0D028684UL,
        0x64AF0FEFUL, 0x210F3925UL, 0xB67EC13AUL, 0x97166D14UL, 0xF7E1CDD0UL,
        0x5ADB60E7UL, 0xD5295EBCUL, 0x28833522UL, 0x60EDA8DAUL, 0x7BC76811UL,
        0xAC9FE69DUL, 0x30AB93ECUL, 0x03696614UL, 0x15E3A5B9UL, 0xECC5DC91UL,
        0x1D3B8E97UL, 0x7275E277UL, 0x538E1F4EUL, 0x6CB167DBUL, 0xA7A2F402UL,
        0x2DB35DFEUL, 0xA8BCC22DUL, 0xD8C58A6AUL, 0x6A529B0BUL, 0x0FD43963UL,
        0xAFC17A97UL, 0x943C3C74UL, 0x95138769UL, 0x6F4E0772UL, 0xB143B688UL,
        0x3B18E752UL, 0x69D2E4AEUL, 0x8107C9FFUL, 0xCDBC62E2UL, 0x5781414FUL,
        0x8B87437EUL, 0xA70E1101UL, 0x91DABC65UL, 0x4E232CD0UL, 0x229749B5UL,
        0xD7386806UL, 0xB3C3F24BUL, 0x60DC5207UL, 0x0BDB9C30UL, 0x1A70E7E9UL,
        0xF37C71D5UL, 0x44B89B08UL, 0xB4D2F976UL, 0xB40E27BCUL, 0xFFDF8A80UL,
        0x9C411A2AUL, 0xD0F7B37DUL, 0xEF53CEC4UL, 0xECA4D58AUL, 0x0B923200UL,
        0xCF22E064UL, 0x8EBFA303UL, 0xF7CF814CUL, 0x32AE2A2BUL, 0xB5E13DAEUL,
        0xC998F9FFUL, 0x349947B0UL, 0x29CF72CEUL, 0x17E38F85UL, 0xF3B26129UL,
        0xD45D6D81UL, 0x09B3CE98UL, 0x860536B8UL, 0xE5792E1BUL, 0x12AD6419UL,
        0xF5F71C69UL, 0xCBC8B7C2UL, 0x8F651659UL, 0xA0CC74F3UL, 0xD78CB99EUL,
        0x51C08D83UL, 0x29F55449UL, 0x002ED713UL, 0x38A824F3UL, 0x57161DF6UL,
        0x7452E319UL, 0x25890E2EUL, 0xC7442433UL, 0x4A5F6355UL, 0x6A83E1E0UL,
        0x823CEDB6UL, 0xF1D444EBUL, 0x88381097UL, 0x5DE3743EUL, 0x46CA4F9AUL,
        0xD8370487UL, 0xEDEC154AUL, 0x433F1AFBUL, 0xF5FAD54FUL, 0x98DB2FB4UL,
        0xE448E96DUL, 0xF650E4C8UL,
};

static void test_next_once(void)
{
    isaac_ctx_t ctx;
    memset(&ctx, 0, sizeof(ctx)); // Zero seed
    isaac_init(&ctx, true);

    const uint32_t next = isaac_next(&ctx);

    atto_eq(next, expected_next_results[0]);
}

static void test_next_all(void)
{
    uint32_t result;
    isaac_ctx_t ctx;
    memset(&ctx, 0, sizeof(ctx));
    isaac_init(&ctx, true);
    for (uint_fast32_t i = 0; i < EXPECTED_NEXT_ELEMENTS; i++)
    {
        result = isaac_next(&ctx);
        atto_eq(result, expected_next_results[i]);
    }
    puts("");
}

void test_isaac_next(void)
{
    test_next_once();
    test_next_all();
}
