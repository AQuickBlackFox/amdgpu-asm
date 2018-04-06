	.hsa_code_object_version 2,1
	.hsa_code_object_isa 9,0,0,"AMD","AMDGPU"
	.p2align	8
	.type	hello_world,@function
	.amdgpu_hsa_kernel hello_world
hello_world:
.Lfunc_begin0:
	.amd_kernel_code_t
                enable_sgpr_kernarg_segment_ptr = 1
                float_mode = 192
                enable_ieee_mode = 1
                enable_trap_handler = 1
                is_ptr64 = 1
                compute_pgm_rsrc1_vgprs = 0
                compute_pgm_rsrc1_sgprs = 0
                compute_pgm_rsrc2_user_sgpr = 2
                kernarg_segment_byte_size = 12
              wavefront_sgpr_count = 3
              workitem_vgpr_count = 3
	.end_amd_kernel_code_t
        s_load_dword s2, s[0:1], 0x8
        ; we prefetch the first argument,
        ; its good for performance
	s_load_dwordx2 s[0:1], s[0:1], 0x0
        v_lshlrev_b32 v0, 2, v0
        s_waitcnt lgkmcnt(1)
        s_cmp_eq_u32 s2, 0
        s_cbranch_scc1 BB0_2
;
        s_waitcnt lgkmcnt(0)
        v_mov_b32_e32 v1, s1
        v_add_co_u32 v0, vcc, v0, s0
        v_addc_co_u32 v1, vcc, v1, 0, vcc
        flat_load_dword v2, v[0:1]
        s_waitcnt vmcnt(0)
BB0_1:
        v_add_f32 v2, v2, 1.0
        s_sub_u32 s2, s2, 1
        s_cmp_gt_u32 s2, 0
        s_cbranch_scc1 BB0_1

        flat_store_dword v[0:1], v2
        s_waitcnt vmcnt(0) lgkmcnt(0)
BB0_2:
	s_endpgm
.Lfunc_end0:
	.size	hello_world, .Lfunc_end0-hello_world

