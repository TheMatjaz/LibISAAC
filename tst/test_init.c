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

const static isaac_ctx_t zero_initialised_ctx = {
        .next32_index = ISAAC_U32_ELEMENTS - 1,
        .next8_index = 0,
        .a = 0x44D22B48UL,
        .b = 0x182600F3UL,
        .c = 0x00000001UL,
        .result = {
                0xE76DD339UL, 0xD91AA738UL, 0xD32956E5UL, 0xA264E933UL,
                0x3DD20023UL, 0x456F1EDDUL, 0x96C59CF4UL, 0xD3A388FCUL,
                0x5D89A1C1UL, 0x49F413FCUL, 0x4873D91EUL, 0x2F840E43UL,
                0xED6ABD62UL, 0x10C8A5ABUL, 0x43C1A57BUL, 0xD70B1E10UL,
                0x8173DC04UL, 0x53F78EAAUL, 0x89651D84UL, 0xD5BE7FFAUL,
                0x6F57E7CEUL, 0x9C8AC447UL, 0x0073E342UL, 0x365AA66CUL,
                0x97661C5EUL, 0xAF90E49EUL, 0x8C090A23UL, 0x0E864542UL,
                0x3DE0DF39UL, 0xBF7AF48EUL, 0x13871BE7UL, 0x3E7A8B49UL,
                0x4207D36FUL, 0x4A8EC630UL, 0x0A06B272UL, 0x66907654UL,
                0x9DED8244UL, 0x32028BB8UL, 0x4C3901C6UL, 0xB6470834UL,
                0x621BD7CAUL, 0xF313ADECUL, 0x2F659883UL, 0x9E979702UL,
                0xBBADD184UL, 0x03DD14A5UL, 0x43ABC21CUL, 0x565E2229UL,
                0x89DAE927UL, 0x60060AFBUL, 0xCA890B31UL, 0xD5253552UL,
                0xAD2BA480UL, 0xE1194B0EUL, 0x2D845C0DUL, 0x97A48E53UL,
                0xC7EFBC2FUL, 0x9971E496UL, 0x80D8C2DEUL, 0xA0E5710BUL,
                0x0F955969UL, 0xB566E14CUL, 0x0B0CD6DAUL, 0xE5F489F6UL,
                0x2C907ADEUL, 0x7BE3F02EUL, 0x71F63B07UL, 0x09E6E57FUL,
                0x4C373E7AUL, 0xC99A2639UL, 0x54713D17UL, 0x11F0831AUL,
                0x76AA1C4EUL, 0xDBF57F01UL, 0x8B2160A8UL, 0x2B2F4C09UL,
                0xCC5E6974UL, 0xFDE283C4UL, 0x8B9E6B94UL, 0x801A89CAUL,
                0x651B11C0UL, 0x360D41CDUL, 0xBF2443D6UL, 0x79801FD5UL,
                0xD95F25B3UL, 0xB849D785UL, 0x5FC7C5F3UL, 0x368D3D00UL,
                0x85C5EEC2UL, 0x7E2F5520UL, 0x41BA2ADCUL, 0x5C509848UL,
                0x0761DC80UL, 0x872783A4UL, 0x71CE907CUL, 0x52801FA8UL,
                0x64E8E3F4UL, 0x5D21D51EUL, 0xF4930DBAUL, 0x3B347002UL,
                0x4EB6BD32UL, 0xF9585A3AUL, 0x7A60FABDUL, 0x49ECF97AUL,
                0x82FCCAEBUL, 0xFFB8AB5CUL, 0x1844CEE2UL, 0x161F5CA6UL,
                0xAF5CFCABUL, 0x332C95D6UL, 0xA5B5981DUL, 0x99D8D9E6UL,
                0x6095EFCBUL, 0xADE6E428UL, 0x290A1140UL, 0x67822B45UL,
                0x359AC366UL, 0xFB253454UL, 0x8B8E753CUL, 0x7CAB12F6UL,
                0xE15000A6UL, 0x4AF40896UL, 0x5B6FB132UL, 0xFD84B19BUL,
                0xA43A1D02UL, 0x672C3725UL, 0x9D21AC42UL, 0x3FF4CC70UL,
                0xE41EA465UL, 0xE3BB2064UL, 0x44C4D79DUL, 0x44D6E893UL,
                0x436385C6UL, 0xB310D06EUL, 0xDF8BE548UL, 0x2992DFC6UL,
                0xB2CBD9E4UL, 0x80B4B915UL, 0xB3FC5C66UL, 0x7A725BB2UL,
                0x4C655B84UL, 0x1AD1D764UL, 0x1D3043EBUL, 0xB0CC336BUL,
                0x6B2F4538UL, 0x3D29669BUL, 0x6275ACF3UL, 0x08DFD64FUL,
                0x36658201UL, 0x007E96A3UL, 0x003A02F5UL, 0xDBF38A8FUL,
                0x205530EEUL, 0xB3310333UL, 0x7DFC8C7FUL, 0x10B22A22UL,
                0x9CC17BCCUL, 0xC6BA1971UL, 0xC230E2ACUL, 0xDD5E06C6UL,
                0x3F07EC49UL, 0x1AD3D9D5UL, 0x765F0DBAUL, 0xC5418124UL,
                0x060DED54UL, 0xFA55319BUL, 0x5B563101UL, 0xB831AD14UL,
                0x9C7DC323UL, 0xE099BAF1UL, 0x7F081C9AUL, 0xB7CFA23CUL,
                0xD7E48546UL, 0x4FBB94BEUL, 0xB10B5D29UL, 0x7C53C9B2UL,
                0x0935AD6EUL, 0xCC5FFF02UL, 0xE34802D5UL, 0x03359832UL,
                0x4DAC20DBUL, 0xBAF0406DUL, 0x15D565B4UL, 0x1BDF1FD0UL,
                0x394B8A4FUL, 0x2E7EA9EDUL, 0x0F2969E4UL, 0x890A740CUL,
                0xDE342516UL, 0x9026D97EUL, 0x9521825FUL, 0x6F359A39UL,
                0x98CB3F8BUL, 0x02C0D8ABUL, 0x902B347DUL, 0x1FFE0E04UL,
                0xF460BDF1UL, 0xA7DC6E56UL, 0x17CB7EBFUL, 0xB026016DUL,
                0xED6E963BUL, 0x72EB767BUL, 0xBEF63EEAUL, 0x6F461810UL,
                0x7BBA5EADUL, 0x5D3C00EAUL, 0x4CFDD254UL, 0x675CC8AEUL,
                0xB97FFABEUL, 0x2492D476UL, 0x4E83930AUL, 0x26F0774DUL,
                0x4B90A4DEUL, 0x6BE6CE81UL, 0x19CA2158UL, 0xA358EB94UL,
                0x42D19CD7UL, 0xC7041EAEUL, 0xE8B4F627UL, 0x02E17B6FUL,
                0xFB8A0E99UL, 0x9E604C7BUL, 0xC01EDA0DUL, 0xEAD4A900UL,
                0x842131C4UL, 0x472FD994UL, 0xC6ACD20FUL, 0x44D3FF79UL,
                0x05C04FCEUL, 0x67648B17UL, 0xF27C4D0DUL, 0x0016E86FUL,
                0x1629CFA4UL, 0xAC450B8FUL, 0x5AB3EAB9UL, 0xF4C75E24UL,
                0x25C871BDUL, 0xBAE16FFAUL, 0x6249FA29UL, 0xC5C29E18UL,
                0xA658F57AUL, 0xC90F8FBDUL, 0x347CB71DUL, 0x96C33F74UL,
                0xCC4C9AFBUL, 0x894F41C2UL, 0x52251DEFUL, 0x5F071FAFUL,
                0x0FC99C24UL, 0xB3FFA8B5UL, 0x995206E9UL, 0x296FD679UL,
                0xB08ACD21UL, 0x301B6622UL, 0x300B4A8DUL, 0x182600F3UL,
        },
        .mem = {
                0x56047A81UL, 0xD6660599UL, 0xB0159A4BUL, 0x1964DC2AUL,
                0x4D02426CUL, 0x680F6195UL, 0xB04CD769UL, 0x111784BDUL,
                0x267304AEUL, 0x7E452F48UL, 0x02CFF7EDUL, 0xCC6E7889UL,
                0x7D3A535AUL, 0x368EE3C0UL, 0x3F4D802CUL, 0xEE189E9EUL,
                0x636D350EUL, 0x59FD99BFUL, 0xC5A22983UL, 0x4B9A5D5BUL,
                0xC44709DBUL, 0x8963FFFDUL, 0xE54CDF4AUL, 0x6EFC9DA6UL,
                0x342747D5UL, 0x6059E6C1UL, 0x90F40656UL, 0x4B856B3AUL,
                0xD4938010UL, 0xA4FD5D58UL, 0xA4B0B885UL, 0xD9A91123UL,
                0x1EE04B6EUL, 0x431179CAUL, 0x5D6CC052UL, 0xFA9154A5UL,
                0x8CD4172EUL, 0xD47370C5UL, 0xACD17676UL, 0xAAFD346CUL,
                0x0730712EUL, 0x4793AE8FUL, 0x1C8DE502UL, 0x0B9CFC2AUL,
                0x64DD9D3CUL, 0x51662EB9UL, 0xC9AFBC40UL, 0x1E75E1EDUL,
                0x4FD4B058UL, 0xB370C197UL, 0xE15A7BC3UL, 0x382E20DDUL,
                0x0F033383UL, 0xCB00DC0EUL, 0xEF044CFEUL, 0xAAF5BE3AUL,
                0xF225175CUL, 0x8A763188UL, 0x4B6A6914UL, 0x7A8BC1AFUL,
                0x055C7C5BUL, 0xFE806425UL, 0x4BF9A494UL, 0x016237DFUL,
                0xE2B7C2EDUL, 0x6F1E8850UL, 0x7B5BEA0BUL, 0x1D350613UL,
                0xF94E29D7UL, 0x55E92FC1UL, 0xD2915DEAUL, 0xF9F3056AUL,
                0x121B3F69UL, 0xC372FD8DUL, 0xD0351E64UL, 0xCA043916UL,
                0x333FD62EUL, 0x17C4675CUL, 0xA3308EA2UL, 0x13D07F95UL,
                0x09F2E14FUL, 0x468AC80FUL, 0xE51350AAUL, 0x85DCB3B5UL,
                0xC1EFA9DEUL, 0xFAB45C5EUL, 0xAA0775EAUL, 0x70B6A4E2UL,
                0x5B3DCE84UL, 0xE8C59569UL, 0xE16DCCE9UL, 0xEAC9C903UL,
                0x1699D5E9UL, 0xB5CE752DUL, 0x308A48F0UL, 0xBCD5C1C1UL,
                0x3CC4E2D1UL, 0xE352A810UL, 0xD6B0C688UL, 0x635E1F45UL,
                0x16FF3856UL, 0x26531989UL, 0x71CE5DD0UL, 0x65031613UL,
                0x425CC84AUL, 0xFDB8F9FAUL, 0x6B648799UL, 0x4EE1A639UL,
                0xEB6E08D8UL, 0x6A88A258UL, 0xA6052D21UL, 0x1DFF3029UL,
                0x05413972UL, 0xDEB88917UL, 0x174EFAB6UL, 0xA04C6A47UL,
                0x63E63F81UL, 0x7089166CUL, 0x893228ADUL, 0xEB4AEAB0UL,
                0x10A09BCEUL, 0x79B46D63UL, 0x69CC919DUL, 0xC17E302EUL,
                0x507EE56EUL, 0x07CE5735UL, 0xF63CD88FUL, 0xFEA8825AUL,
                0xEBD212E0UL, 0x75FFDD9BUL, 0xBD9EC967UL, 0xF2BEF723UL,
                0x029870B3UL, 0x3AABD08BUL, 0x64397764UL, 0x08CE3411UL,
                0x49BC47CFUL, 0xEBC3AC04UL, 0x0DE2E3D4UL, 0x3828E437UL,
                0x1F2F9253UL, 0x3F2A57A8UL, 0xB51BDA32UL, 0xED498E86UL,
                0xD2C9F6ACUL, 0xA6277381UL, 0x15A46AD7UL, 0xFA54E657UL,
                0xB49479B8UL, 0x95F4B195UL, 0xDB4F1703UL, 0x54745A14UL,
                0x02B8C3BCUL, 0xFEA14978UL, 0xADAA80AEUL, 0x2432FCEDUL,
                0xF4BB0FC2UL, 0x87F6A407UL, 0x0C15F24CUL, 0x790FADF4UL,
                0x50768D28UL, 0x349613C7UL, 0x37706F90UL, 0xE047B5B6UL,
                0x162955D1UL, 0x46C6E562UL, 0xCF705694UL, 0x92A3784BUL,
                0x4CD24CE0UL, 0x3A63529DUL, 0xC980D939UL, 0x916E65C4UL,
                0x27EA2D1EUL, 0x77AD2339UL, 0x357A61C2UL, 0x136A3C91UL,
                0xDC95F925UL, 0x8B8EAAB8UL, 0x6E2AAD60UL, 0xC3EACBD6UL,
                0x1073C6DAUL, 0x4D563DAAUL, 0x1AD0295EUL, 0xF23FDA54UL,
                0x4FFBD744UL, 0xD078808CUL, 0xA6DF9D7EUL, 0x3A07F30BUL,
                0xD4D215BBUL, 0x9E500712UL, 0x870F1587UL, 0x03DF99B3UL,
                0xE169A893UL, 0x5D2A027AUL, 0x4AB44EC3UL, 0xCC62B27CUL,
                0x20BA6CA2UL, 0xD87A7520UL, 0x76EFE0A6UL, 0x31CFD74DUL,
                0xB64AECFBUL, 0x940EB075UL, 0xAB49E8CCUL, 0x701197E4UL,
                0xC727F8DFUL, 0x46BD41D1UL, 0x71BC4B57UL, 0x554FB27EUL,
                0x12B495B8UL, 0x9821182DUL, 0x57A0604EUL, 0x65AE4A6EUL,
                0xAD97E5E7UL, 0x16E762B1UL, 0xFCFA8F34UL, 0x5CA18F54UL,
                0x3406A083UL, 0xA1B194A6UL, 0x252DB296UL, 0x43EC0FD6UL,
                0x26947429UL, 0x6CB12FA2UL, 0x6D38A4B2UL, 0x4A2A37A9UL,
                0x6B6ED101UL, 0xFD188437UL, 0xEDD7CA76UL, 0x96308533UL,
                0xC85C8D86UL, 0x4179BC36UL, 0x35F7378EUL, 0x0B6DB466UL,
                0x1C48AC39UL, 0x0C1F6996UL, 0x715810A9UL, 0x7AAED007UL,
                0x103F536AUL, 0x89A9463FUL, 0x0325DD28UL, 0x5E97B57FUL,
                0x4CFA9BB6UL, 0x24E5084FUL, 0x65C9E59DUL, 0xC4CD2945UL,
                0x7F9184C4UL, 0xC1AADE8AUL, 0x10E5AE0BUL, 0x35B2CADDUL,
                0xEAF5E211UL, 0x8FDE8CA6UL, 0x5FC82277UL, 0x58AD1181UL,
                0x3D710A71UL, 0x0B10C32FUL, 0x94BB36D6UL, 0x71D80509UL,
        }
};

const static isaac_ctx_t no_seed_ctx = {
        .next32_index = ISAAC_U32_ELEMENTS - 1,
        .next8_index = 0,
        .a = 0x3923441EUL,
        .b = 0x71D71FD2UL,
        .c = 0x00000001UL,
        .result = {
                0x9FC09148UL, 0xF989E740UL, 0x0898E634UL, 0x6E4D10EFUL,
                0xFEE2D7E8UL, 0xECD81B8FUL, 0xCF5E308AUL, 0x1719F4FDUL,
                0xAB8FAE88UL, 0xAEC1B3CFUL, 0x61CC2C63UL, 0xB656F150UL,
                0xCB74716DUL, 0x90BB5ED4UL, 0xA72976AFUL, 0x5CAD2ED8UL,
                0x78A26D4FUL, 0x8C482122UL, 0x91E4717CUL, 0x0CF4970DUL,
                0x39E42A43UL, 0x02FCDCA2UL, 0x5256916FUL, 0x91381311UL,
                0x41F93691UL, 0xF0EF1488UL, 0x57891E14UL, 0x48E0C613UL,
                0x79BA733AUL, 0x9B53E178UL, 0xDDB946FBUL, 0x1F05D840UL,
                0x73579EA5UL, 0xEBF5E15EUL, 0x2AAD2C2DUL, 0x251A36BBUL,
                0x0F981EBEUL, 0xE4CEDF21UL, 0x3EE87A9EUL, 0xD80D0FABUL,
                0x1FB3199EUL, 0x4EA70E5CUL, 0x9E4B911AUL, 0x4DA6F464UL,
                0xF8B2D53EUL, 0x7BB70B9AUL, 0x29E7F406UL, 0xB1FC7819UL,
                0x5D014587UL, 0xE4DE0148UL, 0xFEB7C855UL, 0xB2FA0FFCUL,
                0x418D4BC3UL, 0x62E70953UL, 0x624B9C48UL, 0xC61BFE6AUL,
                0x026C202BUL, 0x61328608UL, 0x797D8B28UL, 0xBE162273UL,
                0x31321C2CUL, 0x77A77AB8UL, 0x55B5C622UL, 0xA75F163EUL,
                0x67743A32UL, 0x85A4A491UL, 0x4FE51302UL, 0x9A9B17ECUL,
                0x1CBCF183UL, 0x34CC217AUL, 0x7070E101UL, 0x0A278BC0UL,
                0x8116D3F9UL, 0x6EB2973AUL, 0x3F73DE7EUL, 0x71BF9B92UL,
                0x93CB9F61UL, 0x7A39691AUL, 0x0485BD0BUL, 0xE268E87BUL,
                0xEE736DC5UL, 0xECDA90E5UL, 0x03DC7F8CUL, 0xA0CFA011UL,
                0x65D958E9UL, 0x0E847B4BUL, 0xB996C3CAUL, 0x69A6BF3DUL,
                0x4A205172UL, 0x42D22CEEUL, 0xF238E206UL, 0x0AA0C112UL,
                0xB24CD963UL, 0xA9F19EBAUL, 0xFB98D55DUL, 0x509E3635UL,
                0xB837CE71UL, 0x33FCE310UL, 0xA9B4EC9BUL, 0xA41408CEUL,
                0xAC150FF7UL, 0xD5F89FA6UL, 0xC0CD0E93UL, 0x90176730UL,
                0x98EC0CB2UL, 0xF6509C35UL, 0x485C8EFBUL, 0xFB5D456DUL,
                0x695488D6UL, 0xB02827E2UL, 0x163CEA45UL, 0xFCDD8FCEUL,
                0xC6CDE1C5UL, 0xC4932E36UL, 0x7F0A3358UL, 0x17AB9860UL,
                0x8E837DC6UL, 0x9A29EA38UL, 0x0D20E049UL, 0x1B332947UL,
                0x9E8C0D05UL, 0x398E45E5UL, 0x6AA570C2UL, 0x5FAA6738UL,
                0x39BA563EUL, 0xA71FB21AUL, 0xE801B9ADUL, 0xA16AC508UL,
                0x79838C09UL, 0x3474D6DEUL, 0xC3F2B2FFUL, 0x07ED8F34UL,
                0x32DA22F0UL, 0xFD831042UL, 0x1584BD04UL, 0x2CD293A9UL,
                0x87DBF4E5UL, 0x4B269588UL, 0x697452B7UL, 0xA376B729UL,
                0x756D762DUL, 0xD1654BAAUL, 0xFD5B3AECUL, 0xF627EC4EUL,
                0xE458CB02UL, 0xFD781E36UL, 0x6FD5690EUL, 0x5C4ED5E6UL,
                0x6F4120C6UL, 0xAF19EDFEUL, 0x40B4E8E6UL, 0xA4D7A224UL,
                0xE7104EF7UL, 0xAAEF5AF3UL, 0x4B7B246AUL, 0xDF8CA205UL,
                0xD5E81B49UL, 0xDFFC0229UL, 0x7494BD80UL, 0x6476151AUL,
                0x38BED333UL, 0xC7E2DD29UL, 0x4ACC13BBUL, 0x9752832EUL,
                0x58F74DB6UL, 0xA89E3B40UL, 0x5B120E3BUL, 0x693B4D7EUL,
                0x48A9330EUL, 0xE1BD4C66UL, 0xB2D27583UL, 0x9F3C34A0UL,
                0xD030C942UL, 0x091265A7UL, 0x90BF5097UL, 0x4518E821UL,
                0x8256F385UL, 0xAD99916DUL, 0x9FCAA17BUL, 0xC99DC8D3UL,
                0xD3788783UL, 0x200CFD47UL, 0xA50C05ACUL, 0x66740461UL,
                0x48A9C0E8UL, 0x573FCAAEUL, 0xE8FAD070UL, 0x7F7F906FUL,
                0x22E0F93CUL, 0xB4499FA2UL, 0x65EEC6D2UL, 0xB3F7EAF3UL,
                0x65788F47UL, 0x1567656AUL, 0x2584CD66UL, 0xA56F2AA4UL,
                0x49653A25UL, 0xA21D52B4UL, 0xCC05180CUL, 0xC7827819UL,
                0x64A35A26UL, 0xED0FB8F5UL, 0x132CC5FBUL, 0x77A1D4AEUL,
                0xA94B48EEUL, 0x9126BD16UL, 0x5541717CUL, 0xC492C7D3UL,
                0xC5D0DE7EUL, 0x62D07F04UL, 0xCAAD4883UL, 0xD68C4E70UL,
                0x6472F663UL, 0x834773A4UL, 0x3A5E9B4FUL, 0xB00F8A99UL,
                0xF4915642UL, 0x1ADD11ECUL, 0x3419BF00UL, 0x4F075A5CUL,
                0x3F06822BUL, 0x70EE28F7UL, 0x556E9B66UL, 0xD7F84AD0UL,
                0x616A5931UL, 0x756D2200UL, 0x408641EDUL, 0x76466653UL,
                0xD87A6368UL, 0xDB2E4911UL, 0xC9C2B65EUL, 0xAECB15CCUL,
                0x902EB5F8UL, 0x68392DDEUL, 0xF571A73DUL, 0x5344CB78UL,
                0x0ED850C9UL, 0x6EF0A079UL, 0xEF585AAEUL, 0xECB934D7UL,
                0xBC12C17FUL, 0x00D6B993UL, 0x0EEFF940UL, 0x500F972EUL,
                0xCA20E846UL, 0xDB452848UL, 0xD82E9489UL, 0x8D048509UL,
                0xFA3CE5BDUL, 0xD83B237FUL, 0x3CB879CAUL, 0x21DC1EA9UL,
                0xC36129FAUL, 0xD4788559UL, 0xB54ADAE7UL, 0x71D71FD2UL,
        },
        .mem = {
                0xC372C203UL, 0xECCD9922UL, 0x6F30EF44UL, 0xAF33DFF9UL,
                0x1E1B61ECUL, 0x0D86FB19UL, 0xDA03D964UL, 0x782D3C57UL,
                0x3407B931UL, 0xC4BAA225UL, 0x72549105UL, 0x847FD17AUL,
                0x076C1D0CUL, 0x6B010A26UL, 0x6D77745EUL, 0xED57AF4CUL,
                0xA6F9F250UL, 0x188F8828UL, 0x0CF9FC47UL, 0xCD3D7664UL,
                0x1E2C6372UL, 0x061830DBUL, 0x53B2FDB8UL, 0x4AB3E0CEUL,
                0x3EF35D41UL, 0xD2481849UL, 0xC52D7312UL, 0xD8041E56UL,
                0x7EECBF78UL, 0x9EEE08B1UL, 0x9B3C8574UL, 0xF2AE1D65UL,
                0xE436B3E5UL, 0x9CEE4FCDUL, 0xC66D9030UL, 0xA10CE247UL,
                0xFD3C313DUL, 0x2D7C9FEFUL, 0x054C5266UL, 0x77918017UL,
                0x399767B2UL, 0xE97F31E1UL, 0x0A25EF16UL, 0xD83E6180UL,
                0xDEFC1853UL, 0x5DA6954AUL, 0x86292F0DUL, 0x9A8B6CDAUL,
                0x9843A8A0UL, 0xC8843D82UL, 0x079A993CUL, 0x266A5312UL,
                0x50FD4A23UL, 0xBA14E180UL, 0xD0301AB0UL, 0x9A53059AUL,
                0x56253FB8UL, 0xB3F7655EUL, 0xA2E6465BUL, 0x116CD98EUL,
                0xACF9E18EUL, 0xA8EDE934UL, 0x6C8B7242UL, 0x7B5EC05DUL,
                0xF9C89CA5UL, 0x00DA0325UL, 0xC8388FECUL, 0xFBA7A112UL,
                0x5130D868UL, 0xD2C23C28UL, 0x0B3C1C03UL, 0xC9E96B8AUL,
                0xECFCC4FFUL, 0x25E20594UL, 0x49D95173UL, 0xCA1F5727UL,
                0x0C19582EUL, 0x75EF1A7BUL, 0x606CAD17UL, 0x4776D2D9UL,
                0xE9630322UL, 0xB7BAA0ACUL, 0x03B4869CUL, 0xFB6AABF5UL,
                0x4CD91FB1UL, 0xC6EB55D2UL, 0xEFF70AE2UL, 0x806C07E0UL,
                0xFB506AE0UL, 0x9503D4CAUL, 0x7F22FA25UL, 0x67A27F78UL,
                0x76D56B96UL, 0x402D3191UL, 0xCD1F0267UL, 0x78B4913BUL,
                0x975D23A2UL, 0x0BA7C5ADUL, 0xADB16579UL, 0x430F9FE5UL,
                0xEA0F55AEUL, 0xA4E30828UL, 0x73818E23UL, 0x0921CB37UL,
                0x04A619EBUL, 0xD192BDC2UL, 0xE9FB8FDDUL, 0x996D07CCUL,
                0x6F77A27EUL, 0x5881183BUL, 0x16B4B0D7UL, 0x172D2FFAUL,
                0xF805F811UL, 0xB892D079UL, 0x7455BC99UL, 0x79757EFEUL,
                0x24E92C48UL, 0x16AF555AUL, 0x0F8012E6UL, 0x8E12FED6UL,
                0x8AA6FC6BUL, 0x093E87FCUL, 0xB1F3F7B9UL, 0x28B1BC3CUL,
                0x68E7D212UL, 0xBF0601A2UL, 0x5074D661UL, 0x9BF31996UL,
                0x98B943A1UL, 0xD68BB777UL, 0x3CAABD0DUL, 0x640A7865UL,
                0x267E947FUL, 0x219D4627UL, 0x2A7ED2BEUL, 0x4A1566DFUL,
                0x909D9F1FUL, 0x08BC3013UL, 0x419493E1UL, 0x8057D0FFUL,
                0xAED234D6UL, 0x701ECFE1UL, 0xD3DE5093UL, 0xF528D3EFUL,
                0xA2C0839EUL, 0x73E1268BUL, 0x184D1CB5UL, 0xBCA40018UL,
                0x1C6F2470UL, 0x411021C5UL, 0x470010A5UL, 0x2E70A808UL,
                0xDED43F94UL, 0xD2B88E84UL, 0xA1A402C2UL, 0x186A4763UL,
                0xABC09A42UL, 0x5D108F08UL, 0xF6EF7C02UL, 0xDAFD9D4FUL,
                0x25830052UL, 0x376C9A77UL, 0x3AF7CDA0UL, 0x1A464D20UL,
                0xCECC55BBUL, 0xDB42D2F4UL, 0xC0A7591BUL, 0x223D49E9UL,
                0xCFC9EBC4UL, 0x3C4B6CB9UL, 0x89D8FD16UL, 0x8B10782DUL,
                0x76349749UL, 0x5C99F0D4UL, 0xE337681AUL, 0xF6D693FAUL,
                0x621542E1UL, 0x85F2A4DBUL, 0x240053F2UL, 0x459478F3UL,
                0xCA6DC332UL, 0xE4136659UL, 0x90B2C780UL, 0x08E52078UL,
                0xF93B1362UL, 0x81A93EB2UL, 0x7BB2ECD5UL, 0x68AF6FE0UL,
                0x89E3F308UL, 0x4ABDEE7AUL, 0x1A25EDEDUL, 0xB8FFD191UL,
                0x6A6C42F7UL, 0x4F45DCCBUL, 0x7AF2F606UL, 0x8D5A74C9UL,
                0x717EC71AUL, 0x6D9494B5UL, 0xC1A47207UL, 0xCA49B53FUL,
                0xED4D5C9BUL, 0x34A2F6BCUL, 0x0053055AUL, 0xD143A962UL,
                0x9FBD6B13UL, 0x0758F93CUL, 0x36A0CA9EUL, 0x7A354260UL,
                0xD0530604UL, 0xBEAB7F62UL, 0xE0D772A4UL, 0xF2703B87UL,
                0x9E284DC6UL, 0x36FE8CFAUL, 0xD50FCE1DUL, 0xDFBB03B9UL,
                0x646C5FC8UL, 0x110121AAUL, 0x3C680320UL, 0x3B23E8D5UL,
                0x872654AEUL, 0xC788D396UL, 0x9C942EF4UL, 0xFB964A94UL,
                0x3CF3BF40UL, 0xE058EE68UL, 0xDADFAB68UL, 0x38A62019UL,
                0x87FF0BD1UL, 0xD49F27C9UL, 0xAF17CB57UL, 0x0693D16FUL,
                0x609FC1E7UL, 0xC79BA0CEUL, 0x567B7E00UL, 0x7F148C47UL,
                0x2CFADE44UL, 0xBD5521DFUL, 0x4D6E4314UL, 0x1C722B5BUL,
                0x9A27F479UL, 0xEDD85679UL, 0x135E1125UL, 0xCFE6C353UL,
                0x0A81E053UL, 0x90133DE1UL, 0x10EBBCBFUL, 0x3F405E94UL,
                0xB45AA902UL, 0x40F01CE3UL, 0x86A44128UL, 0x9DBDC9E6UL,
                0x4B0124A1UL, 0x79AC34C8UL, 0x7A8E5D89UL, 0xDB6AE404UL,
        }
};

static void test_init_zero_seed(void)
{
    isaac_ctx_t ctx;
    memset(ctx.result, 0, ISAAC_U32_ELEMENTS);  // Zero seed

    isaac_init(&ctx, true);

    atto_eq(sizeof(ctx), sizeof(zero_initialised_ctx));
    atto_memeq(&ctx, &zero_initialised_ctx, sizeof(ctx));
}

static void test_init_no_seed(void)
{
    isaac_ctx_t ctx;

    isaac_init(&ctx, false);

    atto_eq(sizeof(ctx), sizeof(no_seed_ctx));
    atto_memeq(&ctx, &no_seed_ctx, sizeof(ctx));
}

void test_isaac_init(void)
{
    test_init_zero_seed();
    test_init_no_seed();
}
