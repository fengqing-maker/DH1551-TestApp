
#ifndef IRDEMM_H__INCLUDED__
#define IRDEMM_H__INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * Set temporary variant & sub_variant.
 */
lc_result IRDEMM_SetMigrationVariant(lc_uint16 variant, lc_uint16 subVariant);

/** 
 * Get temporary variant & sub_variant.
 */
lc_result IRDEMM_GetMigrationVariant(lc_uint16 *pVariant, lc_uint16 *pSubVariant);


#ifdef __cplusplus
}
#endif

#endif /* IRDEMM_H__INCLUDED__ */


