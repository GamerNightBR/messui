static const uint8_t fs_imgui_latlong_glsl[646] =
{
	0x46, 0x53, 0x48, 0x03, 0x6f, 0x1e, 0x3e, 0x3c, 0x02, 0x00, 0x11, 0x75, 0x5f, 0x69, 0x6d, 0x61, // FSH.o.><...u_ima
	0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x64, 0x07, 0x01, 0x00, 0x00, // geLodEnabled....
	0x01, 0x00, 0x0a, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0x01, 0x00, // ...s_texColor...
	0x00, 0x01, 0x00, 0x4e, 0x02, 0x00, 0x00, 0x76, 0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x68, // ...N...varying h
	0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x32, 0x20, 0x76, 0x5f, 0x74, 0x65, 0x78, 0x63, // ighp vec2 v_texc
	0x6f, 0x6f, 0x72, 0x64, 0x30, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x68, // oord0;.uniform h
	0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x75, 0x5f, 0x69, 0x6d, 0x61, 0x67, // ighp vec4 u_imag
	0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x64, 0x3b, 0x0a, 0x75, 0x6e, 0x69, // eLodEnabled;.uni
	0x66, 0x6f, 0x72, 0x6d, 0x20, 0x6c, 0x6f, 0x77, 0x70, 0x20, 0x73, 0x61, 0x6d, 0x70, 0x6c, 0x65, // form lowp sample
	0x72, 0x43, 0x75, 0x62, 0x65, 0x20, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, // rCube s_texColor
	0x3b, 0x0a, 0x76, 0x6f, 0x69, 0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, // ;.void main ().{
	0x0a, 0x20, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x72, 0x65, // .  highp vec3 re
	0x73, 0x75, 0x6c, 0x74, 0x5f, 0x31, 0x3b, 0x0a, 0x20, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, // sult_1;.  highp
	0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x3b, 0x0a, // float tmpvar_2;.
	0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x32, 0x20, 0x3d, 0x20, 0x28, 0x76, 0x5f, //   tmpvar_2 = (v_
	0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x2e, 0x78, 0x20, 0x2a, 0x20, 0x36, 0x2e, // texcoord0.x * 6.
	0x32, 0x38, 0x33, 0x31, 0x39, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x68, 0x69, 0x67, 0x68, 0x70, 0x20, // 28319);.  highp
	0x66, 0x6c, 0x6f, 0x61, 0x74, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x33, 0x3b, 0x0a, // float tmpvar_3;.
	0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x33, 0x20, 0x3d, 0x20, 0x28, 0x76, 0x5f, //   tmpvar_3 = (v_
	0x74, 0x65, 0x78, 0x63, 0x6f, 0x6f, 0x72, 0x64, 0x30, 0x2e, 0x79, 0x20, 0x2a, 0x20, 0x33, 0x2e, // texcoord0.y * 3.
	0x31, 0x34, 0x31, 0x35, 0x39, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, // 14159);.  result
	0x5f, 0x31, 0x2e, 0x78, 0x20, 0x3d, 0x20, 0x28, 0x73, 0x69, 0x6e, 0x28, 0x74, 0x6d, 0x70, 0x76, // _1.x = (sin(tmpv
	0x61, 0x72, 0x5f, 0x33, 0x29, 0x20, 0x2a, 0x20, 0x63, 0x6f, 0x73, 0x28, 0x74, 0x6d, 0x70, 0x76, // ar_3) * cos(tmpv
	0x61, 0x72, 0x5f, 0x32, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, // ar_2));.  result
	0x5f, 0x31, 0x2e, 0x79, 0x20, 0x3d, 0x20, 0x63, 0x6f, 0x73, 0x28, 0x74, 0x6d, 0x70, 0x76, 0x61, // _1.y = cos(tmpva
	0x72, 0x5f, 0x33, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74, 0x5f, 0x31, // r_3);.  result_1
	0x2e, 0x7a, 0x20, 0x3d, 0x20, 0x28, 0x2d, 0x28, 0x73, 0x69, 0x6e, 0x28, 0x74, 0x6d, 0x70, 0x76, // .z = (-(sin(tmpv
	0x61, 0x72, 0x5f, 0x33, 0x29, 0x29, 0x20, 0x2a, 0x20, 0x73, 0x69, 0x6e, 0x28, 0x74, 0x6d, 0x70, // ar_3)) * sin(tmp
	0x76, 0x61, 0x72, 0x5f, 0x32, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x6c, 0x6f, 0x77, 0x70, 0x20, // var_2));.  lowp
	0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x34, 0x3b, 0x0a, 0x20, // vec4 tmpvar_4;.
	0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x34, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, //  tmpvar_4.xyz =
	0x74, 0x65, 0x78, 0x74, 0x75, 0x72, 0x65, 0x43, 0x75, 0x62, 0x65, 0x4c, 0x6f, 0x64, 0x20, 0x20, // textureCubeLod
	0x20, 0x20, 0x28, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x2c, 0x20, 0x72, //   (s_texColor, r
	0x65, 0x73, 0x75, 0x6c, 0x74, 0x5f, 0x31, 0x2c, 0x20, 0x75, 0x5f, 0x69, 0x6d, 0x61, 0x67, 0x65, // esult_1, u_image
	0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x64, 0x2e, 0x78, 0x29, 0x2e, 0x78, 0x79, // LodEnabled.x).xy
	0x7a, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x34, 0x2e, 0x77, 0x20, // z;.  tmpvar_4.w
	0x3d, 0x20, 0x28, 0x30, 0x2e, 0x32, 0x20, 0x2b, 0x20, 0x28, 0x30, 0x2e, 0x38, 0x20, 0x2a, 0x20, // = (0.2 + (0.8 *
	0x75, 0x5f, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, // u_imageLodEnable
	0x64, 0x2e, 0x79, 0x29, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x46, 0x72, 0x61, 0x67, // d.y));.  gl_Frag
	0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x3d, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x34, // Color = tmpvar_4
	0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,                                                             // ;.}...
};
static const uint8_t fs_imgui_latlong_dx9[553] =
{
	0x46, 0x53, 0x48, 0x03, 0x6f, 0x1e, 0x3e, 0x3c, 0x01, 0x00, 0x11, 0x75, 0x5f, 0x69, 0x6d, 0x61, // FSH.o.><...u_ima
	0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x64, 0x15, 0x01, 0x00, 0x00, // geLodEnabled....
	0x01, 0x00, 0x04, 0x02, 0x00, 0x03, 0xff, 0xff, 0xfe, 0xff, 0x30, 0x00, 0x43, 0x54, 0x41, 0x42, // ..........0.CTAB
	0x1c, 0x00, 0x00, 0x00, 0x8b, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0x02, 0x00, 0x00, 0x00, // ................
	0x1c, 0x00, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, // ............D...
	0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........P.......
	0x60, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, // `...........t...
	0x00, 0x00, 0x00, 0x00, 0x73, 0x5f, 0x74, 0x65, 0x78, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 0xab, // ....s_texColor..
	0x04, 0x00, 0x0e, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
	0x75, 0x5f, 0x69, 0x6d, 0x61, 0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, // u_imageLodEnable
	0x64, 0x00, 0xab, 0xab, 0x01, 0x00, 0x03, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, // d...............
	0x00, 0x00, 0x00, 0x00, 0x70, 0x73, 0x5f, 0x33, 0x5f, 0x30, 0x00, 0x4d, 0x69, 0x63, 0x72, 0x6f, // ....ps_3_0.Micro
	0x73, 0x6f, 0x66, 0x74, 0x20, 0x28, 0x52, 0x29, 0x20, 0x48, 0x4c, 0x53, 0x4c, 0x20, 0x53, 0x68, // soft (R) HLSL Sh
	0x61, 0x64, 0x65, 0x72, 0x20, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x72, 0x20, 0x39, 0x2e, // ader Compiler 9.
	0x32, 0x39, 0x2e, 0x39, 0x35, 0x32, 0x2e, 0x33, 0x31, 0x31, 0x31, 0x00, 0x51, 0x00, 0x00, 0x05, // 29.952.3111.Q...
	0x01, 0x00, 0x0f, 0xa0, 0x00, 0x00, 0x00, 0x3f, 0xdb, 0x0f, 0xc9, 0x40, 0xdb, 0x0f, 0x49, 0xc0, // .......?...@..I.
	0x00, 0x00, 0x00, 0x00, 0x51, 0x00, 0x00, 0x05, 0x02, 0x00, 0x0f, 0xa0, 0xcd, 0xcc, 0x4c, 0x3f, // ....Q.........L?
	0xcd, 0xcc, 0x4c, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x02, // ..L>............
	0x05, 0x00, 0x00, 0x80, 0x00, 0x00, 0x03, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x98, // ................
	0x00, 0x08, 0x0f, 0xa0, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, 0x01, 0x80, 0x01, 0x00, 0x00, 0xa0, // ................
	0x00, 0x00, 0x00, 0x90, 0x13, 0x00, 0x00, 0x02, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x80, // ................
	0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x55, 0xa0, // ..............U.
	0x01, 0x00, 0xaa, 0xa0, 0x25, 0x00, 0x00, 0x02, 0x01, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x80, // ....%...........
	0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x55, 0x90, 0x01, 0x00, 0x00, 0xa0, // ..........U.....
	0x01, 0x00, 0x00, 0xa0, 0x13, 0x00, 0x00, 0x02, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x80, // ................
	0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x55, 0xa0, // ..............U.
	0x01, 0x00, 0xaa, 0xa0, 0x25, 0x00, 0x00, 0x02, 0x02, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00, 0x80, // ....%...........
	0x05, 0x00, 0x00, 0x03, 0x00, 0x00, 0x01, 0x80, 0x01, 0x00, 0x00, 0x80, 0x02, 0x00, 0x55, 0x80, // ..............U.
	0x05, 0x00, 0x00, 0x03, 0x00, 0x00, 0x04, 0x80, 0x01, 0x00, 0x55, 0x80, 0x02, 0x00, 0x55, 0x81, // ..........U...U.
	0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, 0x80, 0x02, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x02, // ................
	0x00, 0x00, 0x08, 0x80, 0x00, 0x00, 0x00, 0xa0, 0x5f, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0f, 0x80, // ........_.......
	0x00, 0x00, 0xe4, 0x80, 0x00, 0x08, 0xe4, 0xa0, 0x01, 0x00, 0x00, 0x02, 0x00, 0x08, 0x07, 0x80, // ................
	0x00, 0x00, 0xe4, 0x80, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, 0x80, 0x00, 0x00, 0x55, 0xa0, // ..............U.
	0x04, 0x00, 0x00, 0x04, 0x00, 0x08, 0x08, 0x80, 0x00, 0x00, 0x55, 0x80, 0x02, 0x00, 0x00, 0xa0, // ..........U.....
	0x02, 0x00, 0x55, 0xa0, 0xff, 0xff, 0x00, 0x00, 0x00,                                           // ..U......
};
static const uint8_t fs_imgui_latlong_dx11[600] =
{
	0x46, 0x53, 0x48, 0x03, 0x6f, 0x1e, 0x3e, 0x3c, 0x01, 0x00, 0x11, 0x75, 0x5f, 0x69, 0x6d, 0x61, // FSH.o.><...u_ima
	0x67, 0x65, 0x4c, 0x6f, 0x64, 0x45, 0x6e, 0x61, 0x62, 0x6c, 0x65, 0x64, 0x15, 0x00, 0x30, 0x0a, // geLodEnabled..0.
	0x01, 0x00, 0x30, 0x02, 0x44, 0x58, 0x42, 0x43, 0x89, 0x11, 0x25, 0xa6, 0xf5, 0x66, 0x12, 0x3f, // ..0.DXBC..%..f.?
	0xc0, 0x1f, 0x67, 0x9b, 0x6e, 0x4e, 0xac, 0x03, 0x01, 0x00, 0x00, 0x00, 0x30, 0x02, 0x00, 0x00, // ..g.nN......0...
	0x03, 0x00, 0x00, 0x00, 0x2c, 0x00, 0x00, 0x00, 0x84, 0x00, 0x00, 0x00, 0xb8, 0x00, 0x00, 0x00, // ....,...........
	0x49, 0x53, 0x47, 0x4e, 0x50, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, // ISGNP...........
	0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, // 8...............
	0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........D.......
	0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, // ................
	0x53, 0x56, 0x5f, 0x50, 0x4f, 0x53, 0x49, 0x54, 0x49, 0x4f, 0x4e, 0x00, 0x54, 0x45, 0x58, 0x43, // SV_POSITION.TEXC
	0x4f, 0x4f, 0x52, 0x44, 0x00, 0xab, 0xab, 0xab, 0x4f, 0x53, 0x47, 0x4e, 0x2c, 0x00, 0x00, 0x00, // OORD....OSGN,...
	0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........ .......
	0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, // ................
	0x53, 0x56, 0x5f, 0x54, 0x41, 0x52, 0x47, 0x45, 0x54, 0x00, 0xab, 0xab, 0x53, 0x48, 0x44, 0x52, // SV_TARGET...SHDR
	0x70, 0x01, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, 0x59, 0x00, 0x00, 0x04, // p...@.......Y...
	0x46, 0x8e, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa4, 0x00, 0x00, 0x00, 0x5a, 0x00, 0x00, 0x03, // F. .........Z...
	0x00, 0x60, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0x30, 0x00, 0x04, 0x00, 0x70, 0x10, 0x00, // .`......X0...p..
	0x00, 0x00, 0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x62, 0x10, 0x00, 0x03, 0x32, 0x10, 0x10, 0x00, // ....UU..b...2...
	0x01, 0x00, 0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0xf2, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // ....e.... ......
	0x68, 0x00, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x0a, 0x32, 0x00, 0x10, 0x00, // h.......8...2...
	0x00, 0x00, 0x00, 0x00, 0x46, 0x10, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x40, 0x00, 0x00, // ....F........@..
	0xdb, 0x0f, 0xc9, 0x40, 0xdb, 0x0f, 0x49, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ...@..I@........
	0x4d, 0x00, 0x00, 0x07, 0x42, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xd0, 0x00, 0x00, // M...B...........
	0x1a, 0x00, 0x10, 0x80, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4d, 0x00, 0x00, 0x06, // ....A.......M...
	0x32, 0x00, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xd0, 0x00, 0x00, 0x16, 0x05, 0x10, 0x00, // 2...............
	0x00, 0x00, 0x00, 0x00, 0x4d, 0x00, 0x00, 0x06, 0x00, 0xd0, 0x00, 0x00, 0x62, 0x00, 0x10, 0x00, // ....M.......b...
	0x02, 0x00, 0x00, 0x00, 0x06, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x07, // ............8...
	0x82, 0x00, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x2a, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // ........*.......
	0x1a, 0x00, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x07, 0x12, 0x00, 0x10, 0x00, // ........8.......
	0x02, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x10, 0x00, // ................
	0x02, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x0c, 0xf2, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // ....H...........
	0x86, 0x03, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x46, 0x7e, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // ........F~......
	0x00, 0x60, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x80, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, // .`........ .....
	0xa3, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x05, 0x72, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, // ....6...r ......
	0x46, 0x02, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x0a, 0x82, 0x20, 0x10, 0x00, // F.......2.... ..
	0x00, 0x00, 0x00, 0x00, 0x1a, 0x80, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa3, 0x00, 0x00, 0x00, // ...... .........
	0x01, 0x40, 0x00, 0x00, 0xcd, 0xcc, 0x4c, 0x3f, 0x01, 0x40, 0x00, 0x00, 0xcd, 0xcc, 0x4c, 0x3e, // .@....L?.@....L>
	0x3e, 0x00, 0x00, 0x01, 0x00, 0x00, 0x40, 0x0a,                                                 // >.....@.
};
