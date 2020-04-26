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

const static isaac_ctx_t nonzero_initialised_ctx = {
        .next32_index = ISAAC_U32_ELEMENTS - 1,
        .next8_index = 0,
        .a = 0x3FCFDFDAUL,
        .b = 0xC987111FUL,
        .c = 0x00000001UL,
        .result = {
                0x971CD9C6UL, 0xC1FF8E2CUL, 0x0790D1E5UL, 0x42183AB9UL,
                0xF795B85DUL, 0x40117235UL, 0x5E1CB8A2UL, 0x5E59F68AUL,
                0xE2266B16UL, 0x8331A767UL, 0x7CE5A040UL, 0xA7DD8E74UL,
                0x82605046UL, 0xBC506172UL, 0x0E121E85UL, 0x11304761UL,
                0xDD85BE5CUL, 0xBF2D4B76UL, 0x61B69E36UL, 0xA22B58EDUL,
                0xB3F23FE7UL, 0xE1DB8AFCUL, 0x6DE606E2UL, 0x4203B72EUL,
                0x700AE372UL, 0x22662D97UL, 0x647E8AD8UL, 0x394F7918UL,
                0xB9717A59UL, 0x7FB1B5A1UL, 0xF4AD9AC9UL, 0x403F5CB5UL,
                0xC130B1AFUL, 0xD913640CUL, 0xA68F6920UL, 0x37C742F9UL,
                0x0C0F343DUL, 0x039E24C3UL, 0xA43329D1UL, 0x1D4FC93EUL,
                0xD2B774A4UL, 0xE6ECDFA4UL, 0x50F782DEUL, 0xD9BCC32CUL,
                0x2E132954UL, 0x880B875DUL, 0x7ACB9D11UL, 0x25A000CAUL,
                0x3515F508UL, 0x611B883EUL, 0x8FE9004FUL, 0x74E3B0DAUL,
                0xEC597682UL, 0x2E248D9EUL, 0xBDE4D3CCUL, 0xDEA0CFB2UL,
                0xFBCA7BD3UL, 0x4C0206F9UL, 0x92D09662UL, 0xB0F7D772UL,
                0xED891E9AUL, 0x14EA480AUL, 0xB1D4FF64UL, 0xF4375831UL,
                0x5AFB09C2UL, 0xC188454CUL, 0x2AC1D182UL, 0xC8C117D3UL,
                0x9EC3CD34UL, 0x17366CADUL, 0x03A87846UL, 0xC71E5F66UL,
                0x9226F4D5UL, 0x98BDDBEBUL, 0xD6F93CC5UL, 0xBF11FAEDUL,
                0x609649B4UL, 0xD19632B3UL, 0xEF557607UL, 0x0AC8FD47UL,
                0x995049CAUL, 0x73BC5ED7UL, 0x75B9074EUL, 0x374094EFUL,
                0xD7ECD061UL, 0xBD6DC736UL, 0xE3B9F85EUL, 0x3455F76DUL,
                0xA0016F76UL, 0xBC1DB747UL, 0x4003DB22UL, 0x22586EE0UL,
                0xF6BBF1EBUL, 0xB8227AF3UL, 0x78E126ABUL, 0xC6B413C5UL,
                0xF92AE295UL, 0x969F7D8EUL, 0xECE7839FUL, 0xF2811F31UL,
                0x35ED5CB5UL, 0x75C83725UL, 0x4614AB27UL, 0x0179A71CUL,
                0xC6C78665UL, 0x681DDAB0UL, 0x1D2B0B09UL, 0x577EBA9CUL,
                0x96C5A1B6UL, 0x462A0B83UL, 0x1E18D2F4UL, 0x334D3867UL,
                0x409329D9UL, 0xBE47CE95UL, 0x754FF4ADUL, 0xF3D7C990UL,
                0x91F0E9A1UL, 0x7486F9B3UL, 0x65296112UL, 0x69E13398UL,
                0x2A9F0BF4UL, 0x1A2A834CUL, 0x1638F87AUL, 0x54138AB6UL,
                0x53BDD8B5UL, 0x2D83C753UL, 0xE770B14EUL, 0x58A8506FUL,
                0x804457ACUL, 0x72FAB07CUL, 0x510566B6UL, 0xC403FC60UL,
                0xEB16E097UL, 0x001986ECUL, 0x30FFAFF5UL, 0xE0011522UL,
                0x923A1AEFUL, 0x6D55628AUL, 0xA58BF76DUL, 0xFA32CF4DUL,
                0xA57E36A8UL, 0x225DFDD4UL, 0x5F2EDC8FUL, 0xF48CAC1AUL,
                0x594F975FUL, 0x97D51E1DUL, 0xD739A2CDUL, 0x134CDD3BUL,
                0x3EF326EAUL, 0x4DE2B784UL, 0x94A3ACB2UL, 0xB31AA32FUL,
                0xE19EBB47UL, 0x28F80B82UL, 0x19606B42UL, 0xDEB519ACUL,
                0x2A5CA2C8UL, 0x941F5843UL, 0xE73F18E9UL, 0x616ADBAEUL,
                0xC2632062UL, 0x5CFD2F14UL, 0xB346BC60UL, 0xE0F1700AUL,
                0xF76E828AUL, 0x32CCC4EDUL, 0x94464CFFUL, 0xF3E36970UL,
                0x95B5B19DUL, 0xF30AF872UL, 0x871DF567UL, 0x27CDC1ABUL,
                0x045D82B8UL, 0x63553457UL, 0x7E522085UL, 0xFA00E8BDUL,
                0xC5241BFEUL, 0xFA8CFCFAUL, 0xF9A01C7AUL, 0x30CA3DF0UL,
                0x7E4264E4UL, 0x6437FFC9UL, 0xBFA77683UL, 0x0A92D424UL,
                0xC4196AC9UL, 0xD2854C55UL, 0x2DDEE8FCUL, 0x61C5F7CBUL,
                0xD61DCCABUL, 0xA1166856UL, 0x4D0B3FA9UL, 0x89BFAF02UL,
                0x11A4F036UL, 0x84F2C60AUL, 0xBDA4DE39UL, 0x8BA5889AUL,
                0xE5462908UL, 0x6E27FDD7UL, 0xC84CB5C8UL, 0x23F5BE25UL,
                0xA191268DUL, 0x9F00DBC5UL, 0x8093DC57UL, 0x285AAAD7UL,
                0x67B1E46EUL, 0xC10A02AAUL, 0x1C672264UL, 0xFA26FD63UL,
                0x57DA3982UL, 0x856509D1UL, 0x3346749DUL, 0xC7E826DCUL,
                0x25CBD94EUL, 0xD1201B3FUL, 0x7D8A44C3UL, 0x2F9D6B9EUL,
                0xE7B3824AUL, 0xEF3CAE74UL, 0x5244AEDCUL, 0x14CB27E6UL,
                0x72C34521UL, 0x7CE73151UL, 0x4AAD18F4UL, 0x02198D64UL,
                0x5812E873UL, 0x95BACD29UL, 0x3C95A998UL, 0xB0E2B8DAUL,
                0x18A72F1CUL, 0x9A190E08UL, 0x4102234AUL, 0x07109ADCUL,
                0xE8AD45B3UL, 0x801851E3UL, 0xC21F5ABBUL, 0x6D6CF2F5UL,
                0xDE2CC0F2UL, 0xC3206714UL, 0x1B42FAF8UL, 0x2F3EA2B7UL,
                0xB61ECEB4UL, 0xD5EB7091UL, 0x3A6AFE88UL, 0xD96F29CAUL,
                0x9020783BUL, 0xB3C78167UL, 0xA44B1A6CUL, 0x8F8DD09DUL,
                0xBB6EF9CFUL, 0x79879ADEUL, 0x5291E936UL, 0xCB5D7A6EUL,
                0x00861702UL, 0x72F289B6UL, 0x33949FA5UL, 0xC987111FUL,
        },
        .mem = {
                0x4A15F141UL, 0x4FB84986UL, 0x4F575580UL, 0x359CF336UL,
                0xCC3518A7UL, 0x7B627467UL, 0x12616700UL, 0x9064F4BBUL,
                0x87BDB854UL, 0x95F7FED9UL, 0x54FC4DD6UL, 0x9D00978BUL,
                0x20A3B20FUL, 0x4334548CUL, 0xECD0252FUL, 0x4030D8C0UL,
                0x6E4A3695UL, 0x810CCDDEUL, 0x14730E2DUL, 0x2D7CED75UL,
                0x5507D5C7UL, 0xED8DD0D5UL, 0x6F928237UL, 0x96FB76A8UL,
                0x600AC89EUL, 0x56FD3355UL, 0x11788D24UL, 0x63645FBEUL,
                0x835634FEUL, 0x216310E7UL, 0x12BE624FUL, 0xA11B2F54UL,
                0x83AC0A81UL, 0xEDC852B8UL, 0x39066BEAUL, 0x4ED3AB9AUL,
                0xB8B3C6D4UL, 0x3223B8D4UL, 0x97B68A08UL, 0x5C8B2229UL,
                0x05EB5855UL, 0x7D7ADD8CUL, 0x2D19F9E3UL, 0xB573F6B8UL,
                0x1703653FUL, 0xD5D482F1UL, 0x50BCC180UL, 0x1AF18E0EUL,
                0xE8E48682UL, 0x5F07A0C1UL, 0x9643AEBDUL, 0x3546D827UL,
                0xE64C45B1UL, 0x3C8281BDUL, 0x0E7DF5E7UL, 0x814CABBFUL,
                0x79512CD4UL, 0x8D532C12UL, 0xD448D862UL, 0x0DD4EE4EUL,
                0x1BEC7306UL, 0x0DEFDEF8UL, 0x6AA1843CUL, 0x31ECD3A8UL,
                0x572D75B1UL, 0x37111F18UL, 0x32739AF5UL, 0xFE2E6403UL,
                0xA604D35DUL, 0x8A8201A8UL, 0x707F29E9UL, 0x906F5283UL,
                0xA3D647A7UL, 0x4537AC7AUL, 0xC8894E3CUL, 0x194C330AUL,
                0x35970FAAUL, 0xC06F2407UL, 0x65DAE40AUL, 0xD4B09BD9UL,
                0x09A50435UL, 0xF42C0E69UL, 0x06043378UL, 0x39523D4AUL,
                0x298F1AABUL, 0xA0CE3887UL, 0xC188C6BFUL, 0xA8B71F56UL,
                0xBECBEC55UL, 0x74EBD468UL, 0x97C39AD7UL, 0x07AA99D5UL,
                0x020649DDUL, 0xF4B513FEUL, 0xFA653AAEUL, 0x54278AC3UL,
                0xECF7F289UL, 0x7E57DB78UL, 0xD50970F0UL, 0x6B98F4FCUL,
                0xC8C48C05UL, 0x0D184056UL, 0x4BF7CCFEUL, 0xB3201C48UL,
                0x0896892EUL, 0xBADBFAA1UL, 0x44A95A1DUL, 0xB3E22215UL,
                0x6334EA5DUL, 0x136DF83FUL, 0x7A88C2C1UL, 0x865D2BD4UL,
                0x5753F437UL, 0x4A058C4DUL, 0x561A8AD2UL, 0x62F5F4BFUL,
                0xAF298E75UL, 0x8CC94424UL, 0x79695F77UL, 0xE913CA4FUL,
                0x1C72B0CCUL, 0xC4D77D31UL, 0x66DB3A62UL, 0xD27E63A4UL,
                0xB88A0863UL, 0x12DE4CFBUL, 0x2073FA2BUL, 0x936CD61DUL,
                0xF4B7A0B6UL, 0x8E2D84EEUL, 0x3DD28F36UL, 0xA0342CB6UL,
                0x1341BFCCUL, 0xE9776B5BUL, 0x1FCD0021UL, 0xA134C24CUL,
                0xB0F560F4UL, 0x123FA862UL, 0x8CF0EAFFUL, 0x52EA3F93UL,
                0x7713E5F9UL, 0x68AB2DACUL, 0x4D797CE5UL, 0xBA5BC382UL,
                0x49459C2AUL, 0xB74EA93BUL, 0x179FAD75UL, 0x1E4753A1UL,
                0x75CECF1DUL, 0x3815A499UL, 0x9444E0C5UL, 0xDF416704UL,
                0x45F71F08UL, 0x18E01C18UL, 0x2CDB31A3UL, 0x008599F3UL,
                0x7ECD74B4UL, 0x223AF86FUL, 0x0B224AEEUL, 0x7B00071EUL,
                0x4660A4F9UL, 0x1FBF6A03UL, 0xDB5D0F83UL, 0x6092DC96UL,
                0xD098DF2CUL, 0x70F21E04UL, 0x6F885349UL, 0xB67EAC28UL,
                0x079EB9E6UL, 0xF9A20C9EUL, 0xD73E299CUL, 0x7535E0AEUL,
                0x866398ECUL, 0xB7C3529EUL, 0xFE568343UL, 0x4950E38BUL,
                0xFCC1B135UL, 0x3A610542UL, 0xDFF5451BUL, 0x32FA22BCUL,
                0x0728A1D5UL, 0xFA7D4238UL, 0xB652687FUL, 0x932764E4UL,
                0xFBCCFFB7UL, 0x15410B80UL, 0xECA50EDDUL, 0x07A51948UL,
                0x6B47785FUL, 0xCBC0BB27UL, 0x2956623BUL, 0xB79E9F94UL,
                0xFE9DE3F7UL, 0x0F6B1328UL, 0x9DDCDEB2UL, 0xB2AECD08UL,
                0x88CE38CBUL, 0x9BD62FEDUL, 0x9FB73F17UL, 0xA153B164UL,
                0x7DA4AE9DUL, 0x7426982EUL, 0x49156803UL, 0x111FFCF7UL,
                0x4DD1B200UL, 0xA6378FB1UL, 0xEF22E8D6UL, 0x01C9F7BDUL,
                0x19B8F0EBUL, 0x3E01C0C4UL, 0xC9F25D9BUL, 0xAE73CC6AUL,
                0x3E6EB616UL, 0x52402A43UL, 0x902C6F7CUL, 0x782F7492UL,
                0x647FF515UL, 0x9DA6429AUL, 0xAF065DB0UL, 0x417D00C9UL,
                0x571DC9A5UL, 0x79A18D1AUL, 0xE8E70F30UL, 0xCFA6F74DUL,
                0xB1608327UL, 0x0631E802UL, 0x88A12E28UL, 0xAB00DEB7UL,
                0x3F82F3A0UL, 0x77EEC827UL, 0xFD988CBEUL, 0xDC8FA5CEUL,
                0xB1CF8DCEUL, 0xDDC6F5F2UL, 0xB29230E6UL, 0x42ECC2E2UL,
                0xF35E8A50UL, 0xDCA21800UL, 0x0A3BC071UL, 0x5C564059UL,
                0x68E0B3B7UL, 0x990DE98AUL, 0x52383C84UL, 0x5B49E462UL,
                0x991858FFUL, 0xE4A00026UL, 0xE7006EE6UL, 0x89D14DA3UL,
                0x8518D345UL, 0x7BF48382UL, 0x2A60F7E9UL, 0xEB34B41BUL,
                0xE599E4DEUL, 0xD96CD8F3UL, 0xAFC58217UL, 0x8D1D706AUL,
        }
};

static void test_init_zero_seed(void)
{
    isaac_ctx_t ctx;

    isaac_init(&ctx, NULL, 42);
    atto_eq(sizeof(ctx), sizeof(zero_initialised_ctx));
    atto_memeq(&ctx, &zero_initialised_ctx, sizeof(ctx));

    uint8_t dummy[3] = {1, 2, 3};
    isaac_init(&ctx, dummy, 0);
    atto_eq(sizeof(ctx), sizeof(zero_initialised_ctx));
    atto_memeq(&ctx, &zero_initialised_ctx, sizeof(ctx));
}

static void test_init_nonzero_seed(void)
{
    isaac_ctx_t ctx;
    const uint8_t seed[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    isaac_init(&ctx, seed, 8);

    atto_eq(sizeof(ctx), sizeof(nonzero_initialised_ctx));
    atto_memeq(&ctx, &nonzero_initialised_ctx, sizeof(ctx));
}

void test_isaac_init(void)
{
    test_init_zero_seed();
    test_init_nonzero_seed();
}
