/**
 * Copyright (c) 2014 - 2020, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "nrf.h"
#include "app_error.h"
#include "bsp.h"
#include "nrfx_gpiote.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"


const nrfx_gpiote_pin_t m_pin1 = NRF_GPIO_PIN_MAP(1, 1);
const nrfx_gpiote_pin_t m_pin2 = NRF_GPIO_PIN_MAP(1, 2);
const nrfx_gpiote_pin_t m_pin3 = NRF_GPIO_PIN_MAP(1, 3);
const nrfx_gpiote_pin_t m_pin4 = NRF_GPIO_PIN_MAP(1, 4);

static void on_gpio_in_evt(nrfx_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    if (action == NRF_GPIOTE_POLARITY_LOTOHI)
    {
        if (pin == m_pin1)
        {
            NRF_LOG_INFO("pin1 lo to hi");
        }
        else if (pin == m_pin2)
        {
            NRF_LOG_INFO("pin2 lo to hi");
        }
        else if (pin == m_pin3)
        {
            NRF_LOG_INFO("pin3 lo to hi");
        }
        else if (pin == m_pin4)
        {
            NRF_LOG_INFO("pin4 lo to hi");
        }
    }
}

static void gpiote_init()
{
    ret_code_t err_code;
    nrfx_gpiote_in_config_t pir_pin_config = NRFX_GPIOTE_CONFIG_IN_SENSE_LOTOHI(false);

    if (!nrfx_gpiote_is_init())
    {
        NRF_LOG_INFO("Initing gpiote");
        err_code = nrfx_gpiote_init();
        APP_ERROR_CHECK(err_code);
    }

    NRF_LOG_INFO("Declaring gpiote pin sensing");

    err_code = nrfx_gpiote_in_init(m_pin1, &pir_pin_config, on_gpio_in_evt);
    APP_ERROR_CHECK(err_code);
    nrfx_gpiote_in_event_enable(m_pin1, true);

    err_code = nrfx_gpiote_in_init(m_pin2, &pir_pin_config, on_gpio_in_evt);
    APP_ERROR_CHECK(err_code);
    nrfx_gpiote_in_event_enable(m_pin2, true);

    err_code = nrfx_gpiote_in_init(m_pin3, &pir_pin_config, on_gpio_in_evt);
    APP_ERROR_CHECK(err_code);
    nrfx_gpiote_in_event_enable(m_pin3, true);

    err_code = nrfx_gpiote_in_init(m_pin4, &pir_pin_config, on_gpio_in_evt);
    APP_ERROR_CHECK(err_code);
    nrfx_gpiote_in_event_enable(m_pin4, true);
 }

/** @brief Function for main application entry.
 */
int main(void)
{
    APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
    NRF_LOG_DEFAULT_BACKENDS_INIT();

    NRF_LOG_INFO("Started gpiote nrfx");

    gpiote_init();

    while (true)
    {
        NRF_LOG_INFO("About to sleep");
        NRF_LOG_FINAL_FLUSH();
        NRF_POWER->SYSTEMOFF = 1;
    }
}


/** @} */
