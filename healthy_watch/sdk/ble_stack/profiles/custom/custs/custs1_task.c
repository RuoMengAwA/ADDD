/**
****************************************************************************************
*
* @file custs1_task.c
*
* @brief Custom Service profile task source file.
*
* Copyright (C) 2014. Dialog Semiconductor Ltd, unpublished work. This computer 
* program includes Confidential, Proprietary Information and is a Trade Secret of 
* Dialog Semiconductor Ltd.  All use, disclosure, and/or reproduction is prohibited 
* unless authorized in writing. All Rights Reserved.
*
* <bluetooth.support@diasemi.com> and contributors.
*
****************************************************************************************
*/
#include "rwble_config.h"              // SW configuration
#if (BLE_CUSTOM1_SERVER)
#include "custs1_task.h"
#include "custs1.h"
#include "custom_common.h"
#include "attm_db_128.h"
#include "ke_task.h"
#include "gapc.h"
#include "gapc_task.h"
#include "gattc_task.h"
#include "attm_db.h"
#include "atts_util.h"
#include "prf_utils.h"
#include "app_prf_types.h"
#include "attm_util.h"

#include "user_custs1_def.h"

#if (BLE_CUSTOM_SERVER)
#include "user_custs_config.h"
#endif // (BLE_CUSTOM_SERVER)

#include "LIS2DS12_ACC_driver.h"
#include "spi_flash.h"
#include "string.h"
//*****************************************dgh
extern unsigned char Heart_Rate[2];//心率数据
extern unsigned char Steps[5] ;//步数
extern unsigned char Calorie[5] ;//卡路里
extern void DataConversion(void);
extern u8_t dghData[20];
extern u16_t Number_Of_Steps;
extern unsigned char hr_capture;//capture的心率值
bool dghflag=0;
extern unsigned char  led1_value[20];  //原始数据
extern unsigned char  led2_value[20];
extern unsigned char  led3_value[20];

/*
 * FUNCTION DEFINITIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref CUSTS1_CREATE_DB_REQ message.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */

static int custs1_create_db_req_handler(ke_msg_id_t const msgid,
                                      struct custs1_create_db_req const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    // Database Creation Status
    uint8_t status;
    // Save Profile ID
    custs1_env.con_info.prf_id = dest_id;
    const struct attm_desc *att_db = NULL;    
    uint8_t i=0;
    
    while( cust_prf_funcs[i].task_id != TASK_NONE )
    {
        if( cust_prf_funcs[i].task_id == dest_id)
        {
            if ( cust_prf_funcs[i].att_db != NULL)
            {
                att_db = cust_prf_funcs[i].att_db;
                break;
            } else i++;
        } else i++;
    }

    if ( att_db != NULL )
    {        
        // Create a Database
        status = attm_svc_create_db(&(custs1_env.shdl), param->cfg_flag, param->max_nb_att,
                                        param->att_tbl, dest_id, att_db);
        
        if (status == ATT_ERR_NO_ERROR)
        {
            // save max number of attibutes
            custs1_env.max_nb_att = param->max_nb_att;
            
            // Disable wpt service
            attmdb_svc_set_permission(custs1_env.shdl, PERM(SVC, DISABLE));

            // If we are here, database has been fulfilled with success, go to idle test
            ke_state_set(TASK_CUSTS1, CUSTS1_IDLE);
        }
        
        // Send response to application
        struct custs1_create_db_cfm* cfm = KE_MSG_ALLOC(CUSTS1_CREATE_DB_CFM, src_id, TASK_CUSTS1,
                                                          custs1_create_db_cfm);
        cfm->status = status;
        ke_msg_send(cfm);
    }
    
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref CUSTS1_ENABLE_REQ message.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int custs1_enable_req_handler(ke_msg_id_t const msgid,
                                   struct custs1_enable_req const *param,
                                   ke_task_id_t const dest_id,
                                   ke_task_id_t const src_id)
{
    //Save the connection handle associated to the profile
    custs1_env.con_info.conidx = gapc_get_conidx(param->conhdl);
    //Save the application id
    custs1_env.con_info.appid = src_id;

    // Check if the provided connection exist
    if (custs1_env.con_info.conidx == GAP_INVALID_CONIDX)
    {
        // The connection doesn't exist, request disallowed
        prf_server_error_ind_send((prf_env_struct *)&custs1_env, PRF_ERR_REQ_DISALLOWED,
                                  CUSTS1_ERROR_IND, CUSTS1_ENABLE_REQ);
    }
    else
    {
        //Enable Attributes + Set Security Level
        attmdb_svc_set_permission(custs1_env.shdl, param->sec_lvl);
      
        // Go to connected state
        ke_state_set(TASK_CUSTS1, CUSTS1_CONNECTED);
    }
    
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref GATT_WRITE_CMD_IND message.
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */

static int gattc_write_cmd_ind_handler(ke_msg_id_t const msgid,
                                      struct gattc_write_cmd_ind const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
   uint16_t att_idx, value_hdl;
    uint8_t status = PRF_ERR_OK;
//    uint8_t uuid[GATT_UUID_128_LEN];
//    uint8_t uuid_len;
//    att_size_t len;
//    uint8_t *value;
//    uint16_t perm;
    uint8_t value_buf[20] = {0};
    
    if (KE_IDX_GET(src_id) == custs1_env.con_info.conidx)
    {
        att_idx = param->handle - custs1_env.shdl;
        
			  switch(att_idx)
				{
				  case CUST1_IDX_INDICATEABLE_VAL:
						attmdb_att_set_value(param->handle, param->length, (uint8_t*)&(param->value[0]));
						memcpy(value_buf, &(param->value),param->length);
//						spi_flash_read_data(dghData, 0x03fe00,20);
						Number_Of_Steps=dghData[1];
						hr_capture=dghData[0];
						DataConversion();
						if((value_buf[0] =='s')&&(value_buf[1] == 't')&&(value_buf[2] == 'e')&&(value_buf[3] == 'p'))
						{
							value_buf[0]=Steps[0]+0x30;
							value_buf[1]=Steps[1]+0x30;
							value_buf[2]=Steps[2]+0x30;
							value_buf[3]=Steps[3]+0x30;
							value_buf[4]=Steps[4]+0x30;

							attmdb_att_set_value((custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL), 5, (uint8_t*)&(value_buf[0]));
							prf_server_send_event((prf_env_struct *)&(custs1_env.con_info), false, (custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL));
							hr_capture=0;
						}
						else if((value_buf[0] =='c')&&(value_buf[1] == 'a')&&(value_buf[2] == 'l'))
						{
							value_buf[0]=(Calorie[0])+0x30;
							value_buf[1]=(Calorie[1])+0x30;
							value_buf[2]=(Calorie[2])+0x30;
							value_buf[3]=(Calorie[3])+0x30;
							value_buf[4]=(Calorie[4])+0x30;

							attmdb_att_set_value((custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL), 5, (uint8_t*)&(value_buf[0]));
							prf_server_send_event((prf_env_struct *)&(custs1_env.con_info), false, (custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL));
							hr_capture=0;
						}
						else if((value_buf[0] =='h')&&(value_buf[1] == 'e')&&(value_buf[2] == 'a')&&(value_buf[3] == 'r')&&(value_buf[4] == 't'))
						{
//							value_buf[0]=(Heart_Rate[0])+0x30;
//							value_buf[1]=(Heart_Rate[1])+0x30;
							value_buf[0]=hr_capture/100+0x30;
							value_buf[1]=(hr_capture%100)/10+0x30;
							value_buf[2]=hr_capture%10+0x30;
							attmdb_att_set_value((custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL), 3, (uint8_t*)&(value_buf[0]));
							prf_server_send_event((prf_env_struct *)&(custs1_env.con_info), false, (custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL));
							hr_capture=0;
						}
						else if((value_buf[0] =='r')&&(value_buf[1] == 't')&&(value_buf[2] == 'c'))
						{
							dghData[6]=value_buf[3]-0x30;
							dghData[7]=value_buf[4]-0x30;
							dghData[8]=value_buf[5]-0x30;
							dghData[9]=value_buf[6]-0x30;
							dghData[2]=value_buf[7]-0x30;
							dghData[3]=value_buf[8]-0x30;
							dghData[4]=value_buf[9]-0x30;
							dghData[5]=value_buf[10]-0x30;
//							spi_flash_block_erase(0x040000,SECTOR_ERASE);
//							spi_flash_write_data(dghData, 0x040000,10);
						}
						else if((value_buf[0] =='b')&&(value_buf[1] == 'l')&&(value_buf[2] == 'p'))
						{
							value_buf[0]=dghData[14]/100+0x30;
							value_buf[1]=(dghData[14]%100)/10+0x30;
							value_buf[2]=dghData[14]%10+0x30;
							value_buf[3]=0x2e;
							value_buf[4]=dghData[15]+0x30;
							value_buf[5]=(0)+0x20;
							value_buf[6]=dghData[16]/100+0x30;
							value_buf[7]=(dghData[16]%100)/10+0x30;
							value_buf[8]=dghData[16]%10+0x30;
							value_buf[9]=0x2e;
							value_buf[10]=dghData[17]+0x30;
							attmdb_att_set_value((custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL), 11, (uint8_t*)&(value_buf[0]));
							prf_server_send_event((prf_env_struct *)&(custs1_env.con_info), false, (custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL));
						}
						else if((value_buf[0] =='b')&&(value_buf[1] == 'l')&&(value_buf[2] == 'o'))
						{
							if(dghData[18]%100)
							{
								value_buf[0]=dghData[18]/100+0x30;
								value_buf[1]=(dghData[18]%100)/10+0x30;
								value_buf[2]=dghData[18]%10+0x30;
								value_buf[3]=0x2e;
								value_buf[4]=dghData[19]+0x30;
							}
							else
							{
								value_buf[0]=0x20;
								value_buf[1]=(dghData[18]%100)/10+0x30;
								value_buf[2]=dghData[18]%10+0x30;
								value_buf[3]=0x2e;
								value_buf[4]=dghData[19]+0x30;
							}
							attmdb_att_set_value((custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL), 5, (uint8_t*)&(value_buf[0]));
							prf_server_send_event((prf_env_struct *)&(custs1_env.con_info), false, (custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL));
						}
						else if((value_buf[0] =='b')&&(value_buf[1] == 'l')&&(value_buf[2] == 's'))
						{
							value_buf[0]=(0)+0x30;
							value_buf[1]=(0)+0x2e;
							value_buf[2]=(0)+0x30;
							attmdb_att_set_value((custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL), 3, (uint8_t*)&(value_buf[0]));
							prf_server_send_event((prf_env_struct *)&(custs1_env.con_info), false, (custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL));
						}
						else if((value_buf[0] =='l')&&(value_buf[1] == 'e')&&(value_buf[2] == 'd')&(value_buf[3] == '1'))
						{
						//	unsigend char i=0;
							//		i=strlen(led1_value)					
							attmdb_att_set_value((custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL),strlen(led1_value), (uint8_t*)&(led1_value[0]));
							prf_server_send_event((prf_env_struct *)&(custs1_env.con_info), false, (custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL));
//							attmdb_att_set_value((custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL), strlen(led2_value), (uint8_t*)&(led2_value[0]));
//							prf_server_send_event((prf_env_struct *)&(custs1_env.con_info), false, (custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL));
//							attmdb_att_set_value((custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL), strlen(led3_value), (uint8_t*)&(led3_value[0]));
//							prf_server_send_event((prf_env_struct *)&(custs1_env.con_info), false, (custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL));
							
						}
									else if((value_buf[0] =='l')&&(value_buf[1] == 'e')&&(value_buf[2] == 'd')&(value_buf[3] == '2'))
						{
						//	unsigend char i=0;
							//		i=strlen(led1_value)					
//							attmdb_att_set_value((custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL),strlen(led1_value), (uint8_t*)&(led1_value[0]));
//							prf_server_send_event((prf_env_struct *)&(custs1_env.con_info), false, (custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL));
							attmdb_att_set_value((custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL), strlen(led2_value), (uint8_t*)&(led2_value[0]));
							prf_server_send_event((prf_env_struct *)&(custs1_env.con_info), false, (custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL));
//							attmdb_att_set_value((custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL), strlen(led3_value), (uint8_t*)&(led3_value[0]));
//							prf_server_send_event((prf_env_struct *)&(custs1_env.con_info), false, (custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL));
						}
							
								else if((value_buf[0] =='l')&&(value_buf[1] == 'e')&&(value_buf[2] == 'd')&(value_buf[3] == '3'))
						{
						//	unsigend char i=0;
							//		i=strlen(led1_value)					
//							attmdb_att_set_value((custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL),strlen(led1_value), (uint8_t*)&(led1_value[0]));
//							prf_server_send_event((prf_env_struct *)&(custs1_env.con_info), false, (custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL));
//							attmdb_att_set_value((custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL), strlen(led2_value), (uint8_t*)&(led2_value[0]));
//							prf_server_send_event((prf_env_struct *)&(custs1_env.con_info), false, (custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL));
							attmdb_att_set_value((custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL), strlen(led3_value), (uint8_t*)&(led3_value[0]));
							prf_server_send_event((prf_env_struct *)&(custs1_env.con_info), false, (custs1_env.shdl+CUST1_IDX_LONG_VALUE_VAL));
							
						}

						break;
					default:
						break;
				}
			
			/*
        if( att_idx < custs1_env.max_nb_att )
        {   
            // Retrieve UUID
            attmdb_att_get_uuid(param->handle, &uuid_len, &(uuid[0]));
            
            // in case of Client Characteristic Configuration, check validity and set value
            if ((uint16_t)*(uint16_t *)&uuid[0] == DEF_CUST1_INDICATEABLE_UUID)            
            {                
                // Find the handle of the Characteristic Value
                value_hdl = get_value_handle( param->handle );
                if ( !value_hdl ) ASSERT_ERR(0);
                
                // Get permissions to identify if it is NTF or IND.
                attmdb_att_get_permission(value_hdl, &perm);
                status = check_client_char_cfg(PERM_IS_SET(perm, NTF, ENABLE), param);
                
                if (status == PRF_ERR_OK)
                {
                    // Set Client Characteristic Configuration value
                    status = attmdb_att_set_value(param->handle, param->length, (uint8_t*)&(param->value[0]));
                }
            }
            else
            {
                // Call the application function to validate the value before it is written to database
                uint8_t i = 0;
                
                status = PRF_ERR_OK;
                while( cust_prf_funcs[i].task_id != TASK_NONE )
                {
                    if( cust_prf_funcs[i].task_id == dest_id)
                    {
                        if ( cust_prf_funcs[i].value_wr_validation_func != NULL)
                        {
                            status = cust_prf_funcs[i].value_wr_validation_func(att_idx, param->last, param->offset, param->length, (uint8_t *)&param->value[0]);
                            break;
                        } else i++;
                    } else i++;
                }
            
                if (status == PRF_ERR_OK)
                {                    
                    if (param->offset == 0)
                    {
                        // Set value in the database
                        status = attmdb_att_set_value(param->handle, param->length, (uint8_t *)&param->value[0]);
                    }
                    else
                    {
                        // Update value in the database            
                        status = attmdb_att_update_value(param->handle, param->length, param->offset,
                                                            (uint8_t *)&param->value[0]);
                    }
                }
            }
            
            if( (param->last) && (status == PRF_ERR_OK) )
            {
                // Get the value size and data. Can not use param->value, it might be a long value
                if( attmdb_att_get_value(param->handle, &len, &value) != ATT_ERR_NO_ERROR )
                {
                    ASSERT_ERR(0);
                }
                
                //Inform APP                            
                struct custs1_val_write_ind *req_id = KE_MSG_ALLOC_DYN(CUSTS1_VAL_WRITE_IND,
                                                        custs1_env.con_info.appid, custs1_env.con_info.prf_id,
                                                        custs1_val_write_ind,
                                                        len);
                memcpy(req_id->value, (uint8_t*)&value[0], len);
                req_id->conhdl = gapc_get_conhdl(custs1_env.con_info.conidx);    
                req_id->handle = att_idx;
                req_id->length = len;

                ke_msg_send(req_id);
            }                
        }
        else
        {
            status = PRF_ERR_INEXISTENT_HDL;
        }
        */
        // Send Write Response only if client requests for RSP (ignored when 'Write Without Response' is used)
        if (param->response == 1)
        {
            // Send Write Response
            atts_write_rsp_send(custs1_env.con_info.conidx, param->handle, status);
        }
    }
       
    return (KE_MSG_CONSUMED);
    
}    
        
/**
 ****************************************************************************************
 * @brief Handles @ref GATTC_CMP_EVT for GATTC_NOTIFY/GATTC_INDICATE messages meaning that
 * notification/indications has been correctly sent to peer device (but not confirmed by peer device).
 * *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int gattc_cmp_evt_handler(ke_msg_id_t const msgid,  struct gattc_cmp_evt const *param,
                                 ke_task_id_t const dest_id, ke_task_id_t const src_id)
{

    if (param->req_type == GATTC_NOTIFY)
    {
        // Send CFM to APP that value has been sent or not
        struct custs1_val_ntf_cfm *cfm = KE_MSG_ALLOC(  CUSTS1_VAL_NTF_CFM, 
                                                            custs1_env.con_info.appid, custs1_env.con_info.prf_id,
                                                            custs1_val_ntf_cfm);

        cfm->handle = custs1_env.ntf_handle;
        cfm->conhdl = gapc_get_conhdl(custs1_env.con_info.conidx);
        cfm->status = param->status;
        
        ke_msg_send(cfm);
    }
    else if (param->req_type == GATTC_INDICATE)
    {
        // Send CFM to APP that value has been sent or not
        struct custs1_val_ind_cfm *cfm = KE_MSG_ALLOC(  CUSTS1_VAL_IND_CFM, 
                                                            custs1_env.con_info.appid, custs1_env.con_info.prf_id,
                                                            custs1_val_ind_cfm);
        cfm->handle = custs1_env.ind_handle;
        cfm->conhdl = gapc_get_conhdl(custs1_env.con_info.conidx);
        cfm->status = param->status;
        
        ke_msg_send(cfm);
    }
    
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref CUSTS1_VAL_SET_REQ message. 
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int custs1_val_set_req_handler(ke_msg_id_t const msgid,
                                             struct custs1_val_set_req const *param,
                                             ke_task_id_t const dest_id,
                                             ke_task_id_t const src_id)
{
    
    if (param->conhdl == gapc_get_conhdl(custs1_env.con_info.conidx))
    {
        // Update value in DB
        attmdb_att_set_value(custs1_env.shdl + param->handle, param->length, (uint8_t *)&param->value);
    }
    else
    {
        //PRF_ERR_INVALID_PARAM;
    }
    
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref CUSTS1_VAL_NTF_REQ message. 
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int custs1_val_ntf_req_handler(ke_msg_id_t const msgid,
                                             struct custs1_val_ntf_req const *param,
                                             ke_task_id_t const dest_id,
                                             ke_task_id_t const src_id)
{ 
    uint16_t cfg_hdl;
    uint8_t status = PRF_ERR_OK;
    
    if (param->conhdl == gapc_get_conhdl(custs1_env.con_info.conidx))
    {
        uint8_t *cfg_val;
        att_size_t length;

        // Update value in DB
        attmdb_att_set_value(custs1_env.shdl + param->handle, param->length, (uint8_t *)&param->value);

        // Find the handle of the Characteristic Client Configuration
        cfg_hdl = get_cfg_handle( custs1_env.shdl + param->handle, custs1_env.max_nb_att );
        if ( !cfg_hdl ) ASSERT_ERR(0);
        
        // Check if notifications are enabled. 
        attmdb_att_get_value(cfg_hdl, &length, &cfg_val);
        
        // Send indication through GATT
        if ((uint16_t)*((uint16_t*)&cfg_val[0]) == PRF_CLI_START_NTF)
        {
            prf_server_send_event((prf_env_struct *)&custs1_env, 0, custs1_env.shdl + param->handle);
            custs1_env.ntf_handle = param->handle;
        }
        else
        {
            status = PRF_ERR_IND_DISABLED;
        }
    }
    else
    {
        status = PRF_ERR_INVALID_PARAM;
    }
    
    if (status != PRF_ERR_OK)
    {

        // Send CFM to APP that value has been sent or not
        struct custs1_val_ntf_cfm *cfm = KE_MSG_ALLOC( CUSTS1_VAL_NTF_CFM,
                                                   custs1_env.con_info.appid, custs1_env.con_info.prf_id,
                                                   custs1_val_ntf_cfm);
    
        cfm->handle = param->handle;
        cfm->conhdl = gapc_get_conhdl(custs1_env.con_info.conidx);
        cfm->status = status;

        ke_msg_send(cfm);               
    }
    
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles reception of the @ref CUSTS1_VAL_IND_REQ message. 
 * @param[in] msgid Id of the message received (probably unused).
 * @param[in] param Pointer to the parameters of the message.
 * @param[in] dest_id ID of the receiving task instance (probably unused).
 * @param[in] src_id ID of the sending task instance.
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
static int custs1_val_ind_req_handler(ke_msg_id_t const msgid,
                                             struct custs1_val_ind_req const *param,
                                             ke_task_id_t const dest_id,
                                             ke_task_id_t const src_id)
{
    uint16_t cfg_hdl;
    uint8_t status = PRF_ERR_OK;
    
    if (param->conhdl == gapc_get_conhdl(custs1_env.con_info.conidx))
    {
        uint8_t *cfg_val;
        att_size_t length;

        // Update value in DB
        attmdb_att_set_value(custs1_env.shdl + param->handle, param->length, (uint8_t *)&param->value);

        // Find the handle of the Characteristic Client Configuration
        cfg_hdl = get_cfg_handle( custs1_env.shdl + param->handle, custs1_env.max_nb_att);
        if ( !cfg_hdl ) ASSERT_ERR(0);
        
        // Check if indications are enabled.
        attmdb_att_get_value(cfg_hdl, &length, &cfg_val);
        
        // Send indication through GATT
        if ((uint16_t)*((uint16_t*)&cfg_val[0]) == PRF_CLI_START_IND)
        {
            prf_server_send_event((prf_env_struct *)&custs1_env, 1, custs1_env.shdl + param->handle);
            custs1_env.ind_handle = param->handle;
        }
        else
        {
            status = PRF_ERR_IND_DISABLED;
        }
    }
    else
    {
        status = PRF_ERR_INVALID_PARAM;
    }
    
    if (status != PRF_ERR_OK)
    {

        // Send CFM to APP that value has been sent or not
        struct custs1_val_ind_cfm *cfm = KE_MSG_ALLOC( CUSTS1_VAL_IND_CFM,
                                                   custs1_env.con_info.appid, custs1_env.con_info.prf_id,
                                                   custs1_val_ind_cfm);
    
        cfm->handle = param->handle;
        cfm->conhdl = gapc_get_conhdl(custs1_env.con_info.conidx);
        cfm->status = status;

        ke_msg_send(cfm);               
    }
    
    return (KE_MSG_CONSUMED);
}

static int gapc_disconnect_ind_handler(ke_msg_id_t const msgid,
                                      struct gapc_disconnect_ind const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id)
{
    // Check Connection Handle
    if (KE_IDX_GET(src_id) == custs1_env.con_info.conidx)
    {
        custs1_disable(param->conhdl);
    }
    
    return (KE_MSG_CONSUMED);
}

/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */

///Disabled State handler definition.
const struct ke_msg_handler custs1_disabled[] =
{
    {CUSTS1_CREATE_DB_REQ,         (ke_msg_func_t)custs1_create_db_req_handler},
};

///Idle State handler definition.
const struct ke_msg_handler custs1_idle[] =
{
    {CUSTS1_ENABLE_REQ,            (ke_msg_func_t)custs1_enable_req_handler},
};

/// Default State handlers definition
const struct ke_msg_handler custs1_connected[] =
{
    {GATTC_WRITE_CMD_IND,           (ke_msg_func_t)gattc_write_cmd_ind_handler},
    {GATTC_CMP_EVT,                 (ke_msg_func_t)gattc_cmp_evt_handler},
    {CUSTS1_VAL_NTF_REQ,            (ke_msg_func_t)custs1_val_ntf_req_handler},
    {CUSTS1_VAL_SET_REQ,            (ke_msg_func_t)custs1_val_set_req_handler},
    {CUSTS1_VAL_IND_REQ,            (ke_msg_func_t)custs1_val_ind_req_handler},
};

/// Default State handlers definition
const struct ke_msg_handler custs1_default_state[] =
{
    {GAPC_DISCONNECT_IND,           (ke_msg_func_t)gapc_disconnect_ind_handler},
};

/// Specifies the message handler structure for every input state.
const struct ke_state_handler custs1_state_handler[CUSTS1_STATE_MAX] =
{
    [CUSTS1_DISABLED]    = KE_STATE_HANDLER(custs1_disabled),
    [CUSTS1_IDLE]        = KE_STATE_HANDLER(custs1_idle),
    [CUSTS1_CONNECTED]   = KE_STATE_HANDLER(custs1_connected),
};

///Specifies the message handlers that are common to all states.
const struct ke_state_handler custs1_default_handler = KE_STATE_HANDLER(custs1_default_state);

///Defines the place holder for the states of all the task instances.
ke_state_t custs1_state[CUSTS1_IDX_MAX] __attribute__((section("retention_mem_area0"),zero_init)); //@RETENTION MEMORY

#endif // BLE_CUSTOM1_SERVER
