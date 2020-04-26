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

const static uint8_t expected_initialised_ctx[] = {
        0x00, 0x01, 0x00, 0x00, 0x39, 0xD3, 0x6D, 0xE7, 0x38, 0xA7, 0x1A, 0xD9,
        0xE5, 0x56, 0x29, 0xD3, 0x33, 0xE9, 0x64, 0xA2, 0x23, 0x00, 0xD2, 0x3D,
        0xDD, 0x1E, 0x6F, 0x45, 0xF4, 0x9C, 0xC5, 0x96, 0xFC, 0x88, 0xA3, 0xD3,
        0xC1, 0xA1, 0x89, 0x5D, 0xFC, 0x13, 0xF4, 0x49, 0x1E, 0xD9, 0x73, 0x48,
        0x43, 0x0E, 0x84, 0x2F, 0x62, 0xBD, 0x6A, 0xED, 0xAB, 0xA5, 0xC8, 0x10,
        0x7B, 0xA5, 0xC1, 0x43, 0x10, 0x1E, 0x0B, 0xD7, 0x04, 0xDC, 0x73, 0x81,
        0xAA, 0x8E, 0xF7, 0x53, 0x84, 0x1D, 0x65, 0x89, 0xFA, 0x7F, 0xBE, 0xD5,
        0xCE, 0xE7, 0x57, 0x6F, 0x47, 0xC4, 0x8A, 0x9C, 0x42, 0xE3, 0x73, 0x00,
        0x6C, 0xA6, 0x5A, 0x36, 0x5E, 0x1C, 0x66, 0x97, 0x9E, 0xE4, 0x90, 0xAF,
        0x23, 0x0A, 0x09, 0x8C, 0x42, 0x45, 0x86, 0x0E, 0x39, 0xDF, 0xE0, 0x3D,
        0x8E, 0xF4, 0x7A, 0xBF, 0xE7, 0x1B, 0x87, 0x13, 0x49, 0x8B, 0x7A, 0x3E,
        0x6F, 0xD3, 0x07, 0x42, 0x30, 0xC6, 0x8E, 0x4A, 0x72, 0xB2, 0x06, 0x0A,
        0x54, 0x76, 0x90, 0x66, 0x44, 0x82, 0xED, 0x9D, 0xB8, 0x8B, 0x02, 0x32,
        0xC6, 0x01, 0x39, 0x4C, 0x34, 0x08, 0x47, 0xB6, 0xCA, 0xD7, 0x1B, 0x62,
        0xEC, 0xAD, 0x13, 0xF3, 0x83, 0x98, 0x65, 0x2F, 0x02, 0x97, 0x97, 0x9E,
        0x84, 0xD1, 0xAD, 0xBB, 0xA5, 0x14, 0xDD, 0x03, 0x1C, 0xC2, 0xAB, 0x43,
        0x29, 0x22, 0x5E, 0x56, 0x27, 0xE9, 0xDA, 0x89, 0xFB, 0x0A, 0x06, 0x60,
        0x31, 0x0B, 0x89, 0xCA, 0x52, 0x35, 0x25, 0xD5, 0x80, 0xA4, 0x2B, 0xAD,
        0x0E, 0x4B, 0x19, 0xE1, 0x0D, 0x5C, 0x84, 0x2D, 0x53, 0x8E, 0xA4, 0x97,
        0x2F, 0xBC, 0xEF, 0xC7, 0x96, 0xE4, 0x71, 0x99, 0xDE, 0xC2, 0xD8, 0x80,
        0x0B, 0x71, 0xE5, 0xA0, 0x69, 0x59, 0x95, 0x0F, 0x4C, 0xE1, 0x66, 0xB5,
        0xDA, 0xD6, 0x0C, 0x0B, 0xF6, 0x89, 0xF4, 0xE5, 0xDE, 0x7A, 0x90, 0x2C,
        0x2E, 0xF0, 0xE3, 0x7B, 0x07, 0x3B, 0xF6, 0x71, 0x7F, 0xE5, 0xE6, 0x09,
        0x7A, 0x3E, 0x37, 0x4C, 0x39, 0x26, 0x9A, 0xC9, 0x17, 0x3D, 0x71, 0x54,
        0x1A, 0x83, 0xF0, 0x11, 0x4E, 0x1C, 0xAA, 0x76, 0x01, 0x7F, 0xF5, 0xDB,
        0xA8, 0x60, 0x21, 0x8B, 0x09, 0x4C, 0x2F, 0x2B, 0x74, 0x69, 0x5E, 0xCC,
        0xC4, 0x83, 0xE2, 0xFD, 0x94, 0x6B, 0x9E, 0x8B, 0xCA, 0x89, 0x1A, 0x80,
        0xC0, 0x11, 0x1B, 0x65, 0xCD, 0x41, 0x0D, 0x36, 0xD6, 0x43, 0x24, 0xBF,
        0xD5, 0x1F, 0x80, 0x79, 0xB3, 0x25, 0x5F, 0xD9, 0x85, 0xD7, 0x49, 0xB8,
        0xF3, 0xC5, 0xC7, 0x5F, 0x00, 0x3D, 0x8D, 0x36, 0xC2, 0xEE, 0xC5, 0x85,
        0x20, 0x55, 0x2F, 0x7E, 0xDC, 0x2A, 0xBA, 0x41, 0x48, 0x98, 0x50, 0x5C,
        0x80, 0xDC, 0x61, 0x07, 0xA4, 0x83, 0x27, 0x87, 0x7C, 0x90, 0xCE, 0x71,
        0xA8, 0x1F, 0x80, 0x52, 0xF4, 0xE3, 0xE8, 0x64, 0x1E, 0xD5, 0x21, 0x5D,
        0xBA, 0x0D, 0x93, 0xF4, 0x02, 0x70, 0x34, 0x3B, 0x32, 0xBD, 0xB6, 0x4E,
        0x3A, 0x5A, 0x58, 0xF9, 0xBD, 0xFA, 0x60, 0x7A, 0x7A, 0xF9, 0xEC, 0x49,
        0xEB, 0xCA, 0xFC, 0x82, 0x5C, 0xAB, 0xB8, 0xFF, 0xE2, 0xCE, 0x44, 0x18,
        0xA6, 0x5C, 0x1F, 0x16, 0xAB, 0xFC, 0x5C, 0xAF, 0xD6, 0x95, 0x2C, 0x33,
        0x1D, 0x98, 0xB5, 0xA5, 0xE6, 0xD9, 0xD8, 0x99, 0xCB, 0xEF, 0x95, 0x60,
        0x28, 0xE4, 0xE6, 0xAD, 0x40, 0x11, 0x0A, 0x29, 0x45, 0x2B, 0x82, 0x67,
        0x66, 0xC3, 0x9A, 0x35, 0x54, 0x34, 0x25, 0xFB, 0x3C, 0x75, 0x8E, 0x8B,
        0xF6, 0x12, 0xAB, 0x7C, 0xA6, 0x00, 0x50, 0xE1, 0x96, 0x08, 0xF4, 0x4A,
        0x32, 0xB1, 0x6F, 0x5B, 0x9B, 0xB1, 0x84, 0xFD, 0x02, 0x1D, 0x3A, 0xA4,
        0x25, 0x37, 0x2C, 0x67, 0x42, 0xAC, 0x21, 0x9D, 0x70, 0xCC, 0xF4, 0x3F,
        0x65, 0xA4, 0x1E, 0xE4, 0x64, 0x20, 0xBB, 0xE3, 0x9D, 0xD7, 0xC4, 0x44,
        0x93, 0xE8, 0xD6, 0x44, 0xC6, 0x85, 0x63, 0x43, 0x6E, 0xD0, 0x10, 0xB3,
        0x48, 0xE5, 0x8B, 0xDF, 0xC6, 0xDF, 0x92, 0x29, 0xE4, 0xD9, 0xCB, 0xB2,
        0x15, 0xB9, 0xB4, 0x80, 0x66, 0x5C, 0xFC, 0xB3, 0xB2, 0x5B, 0x72, 0x7A,
        0x84, 0x5B, 0x65, 0x4C, 0x64, 0xD7, 0xD1, 0x1A, 0xEB, 0x43, 0x30, 0x1D,
        0x6B, 0x33, 0xCC, 0xB0, 0x38, 0x45, 0x2F, 0x6B, 0x9B, 0x66, 0x29, 0x3D,
        0xF3, 0xAC, 0x75, 0x62, 0x4F, 0xD6, 0xDF, 0x08, 0x01, 0x82, 0x65, 0x36,
        0xA3, 0x96, 0x7E, 0x00, 0xF5, 0x02, 0x3A, 0x00, 0x8F, 0x8A, 0xF3, 0xDB,
        0xEE, 0x30, 0x55, 0x20, 0x33, 0x03, 0x31, 0xB3, 0x7F, 0x8C, 0xFC, 0x7D,
        0x22, 0x2A, 0xB2, 0x10, 0xCC, 0x7B, 0xC1, 0x9C, 0x71, 0x19, 0xBA, 0xC6,
        0xAC, 0xE2, 0x30, 0xC2, 0xC6, 0x06, 0x5E, 0xDD, 0x49, 0xEC, 0x07, 0x3F,
        0xD5, 0xD9, 0xD3, 0x1A, 0xBA, 0x0D, 0x5F, 0x76, 0x24, 0x81, 0x41, 0xC5,
        0x54, 0xED, 0x0D, 0x06, 0x9B, 0x31, 0x55, 0xFA, 0x01, 0x31, 0x56, 0x5B,
        0x14, 0xAD, 0x31, 0xB8, 0x23, 0xC3, 0x7D, 0x9C, 0xF1, 0xBA, 0x99, 0xE0,
        0x9A, 0x1C, 0x08, 0x7F, 0x3C, 0xA2, 0xCF, 0xB7, 0x46, 0x85, 0xE4, 0xD7,
        0xBE, 0x94, 0xBB, 0x4F, 0x29, 0x5D, 0x0B, 0xB1, 0xB2, 0xC9, 0x53, 0x7C,
        0x6E, 0xAD, 0x35, 0x09, 0x02, 0xFF, 0x5F, 0xCC, 0xD5, 0x02, 0x48, 0xE3,
        0x32, 0x98, 0x35, 0x03, 0xDB, 0x20, 0xAC, 0x4D, 0x6D, 0x40, 0xF0, 0xBA,
        0xB4, 0x65, 0xD5, 0x15, 0xD0, 0x1F, 0xDF, 0x1B, 0x4F, 0x8A, 0x4B, 0x39,
        0xED, 0xA9, 0x7E, 0x2E, 0xE4, 0x69, 0x29, 0x0F, 0x0C, 0x74, 0x0A, 0x89,
        0x16, 0x25, 0x34, 0xDE, 0x7E, 0xD9, 0x26, 0x90, 0x5F, 0x82, 0x21, 0x95,
        0x39, 0x9A, 0x35, 0x6F, 0x8B, 0x3F, 0xCB, 0x98, 0xAB, 0xD8, 0xC0, 0x02,
        0x7D, 0x34, 0x2B, 0x90, 0x04, 0x0E, 0xFE, 0x1F, 0xF1, 0xBD, 0x60, 0xF4,
        0x56, 0x6E, 0xDC, 0xA7, 0xBF, 0x7E, 0xCB, 0x17, 0x6D, 0x01, 0x26, 0xB0,
        0x3B, 0x96, 0x6E, 0xED, 0x7B, 0x76, 0xEB, 0x72, 0xEA, 0x3E, 0xF6, 0xBE,
        0x10, 0x18, 0x46, 0x6F, 0xAD, 0x5E, 0xBA, 0x7B, 0xEA, 0x00, 0x3C, 0x5D,
        0x54, 0xD2, 0xFD, 0x4C, 0xAE, 0xC8, 0x5C, 0x67, 0xBE, 0xFA, 0x7F, 0xB9,
        0x76, 0xD4, 0x92, 0x24, 0x0A, 0x93, 0x83, 0x4E, 0x4D, 0x77, 0xF0, 0x26,
        0xDE, 0xA4, 0x90, 0x4B, 0x81, 0xCE, 0xE6, 0x6B, 0x58, 0x21, 0xCA, 0x19,
        0x94, 0xEB, 0x58, 0xA3, 0xD7, 0x9C, 0xD1, 0x42, 0xAE, 0x1E, 0x04, 0xC7,
        0x27, 0xF6, 0xB4, 0xE8, 0x6F, 0x7B, 0xE1, 0x02, 0x99, 0x0E, 0x8A, 0xFB,
        0x7B, 0x4C, 0x60, 0x9E, 0x0D, 0xDA, 0x1E, 0xC0, 0x00, 0xA9, 0xD4, 0xEA,
        0xC4, 0x31, 0x21, 0x84, 0x94, 0xD9, 0x2F, 0x47, 0x0F, 0xD2, 0xAC, 0xC6,
        0x79, 0xFF, 0xD3, 0x44, 0xCE, 0x4F, 0xC0, 0x05, 0x17, 0x8B, 0x64, 0x67,
        0x0D, 0x4D, 0x7C, 0xF2, 0x6F, 0xE8, 0x16, 0x00, 0xA4, 0xCF, 0x29, 0x16,
        0x8F, 0x0B, 0x45, 0xAC, 0xB9, 0xEA, 0xB3, 0x5A, 0x24, 0x5E, 0xC7, 0xF4,
        0xBD, 0x71, 0xC8, 0x25, 0xFA, 0x6F, 0xE1, 0xBA, 0x29, 0xFA, 0x49, 0x62,
        0x18, 0x9E, 0xC2, 0xC5, 0x7A, 0xF5, 0x58, 0xA6, 0xBD, 0x8F, 0x0F, 0xC9,
        0x1D, 0xB7, 0x7C, 0x34, 0x74, 0x3F, 0xC3, 0x96, 0xFB, 0x9A, 0x4C, 0xCC,
        0xC2, 0x41, 0x4F, 0x89, 0xEF, 0x1D, 0x25, 0x52, 0xAF, 0x1F, 0x07, 0x5F,
        0x24, 0x9C, 0xC9, 0x0F, 0xB5, 0xA8, 0xFF, 0xB3, 0xE9, 0x06, 0x52, 0x99,
        0x79, 0xD6, 0x6F, 0x29, 0x21, 0xCD, 0x8A, 0xB0, 0x22, 0x66, 0x1B, 0x30,
        0x8D, 0x4A, 0x0B, 0x30, 0xF3, 0x00, 0x26, 0x18, 0x81, 0x7A, 0x04, 0x56,
        0x99, 0x05, 0x66, 0xD6, 0x4B, 0x9A, 0x15, 0xB0, 0x2A, 0xDC, 0x64, 0x19,
        0x6C, 0x42, 0x02, 0x4D, 0x95, 0x61, 0x0F, 0x68, 0x69, 0xD7, 0x4C, 0xB0,
        0xBD, 0x84, 0x17, 0x11, 0xAE, 0x04, 0x73, 0x26, 0x48, 0x2F, 0x45, 0x7E,
        0xED, 0xF7, 0xCF, 0x02, 0x89, 0x78, 0x6E, 0xCC, 0x5A, 0x53, 0x3A, 0x7D,
        0xC0, 0xE3, 0x8E, 0x36, 0x2C, 0x80, 0x4D, 0x3F, 0x9E, 0x9E, 0x18, 0xEE,
        0x0E, 0x35, 0x6D, 0x63, 0xBF, 0x99, 0xFD, 0x59, 0x83, 0x29, 0xA2, 0xC5,
        0x5B, 0x5D, 0x9A, 0x4B, 0xDB, 0x09, 0x47, 0xC4, 0xFD, 0xFF, 0x63, 0x89,
        0x4A, 0xDF, 0x4C, 0xE5, 0xA6, 0x9D, 0xFC, 0x6E, 0xD5, 0x47, 0x27, 0x34,
        0xC1, 0xE6, 0x59, 0x60, 0x56, 0x06, 0xF4, 0x90, 0x3A, 0x6B, 0x85, 0x4B,
        0x10, 0x80, 0x93, 0xD4, 0x58, 0x5D, 0xFD, 0xA4, 0x85, 0xB8, 0xB0, 0xA4,
        0x23, 0x11, 0xA9, 0xD9, 0x6E, 0x4B, 0xE0, 0x1E, 0xCA, 0x79, 0x11, 0x43,
        0x52, 0xC0, 0x6C, 0x5D, 0xA5, 0x54, 0x91, 0xFA, 0x2E, 0x17, 0xD4, 0x8C,
        0xC5, 0x70, 0x73, 0xD4, 0x76, 0x76, 0xD1, 0xAC, 0x6C, 0x34, 0xFD, 0xAA,
        0x2E, 0x71, 0x30, 0x07, 0x8F, 0xAE, 0x93, 0x47, 0x02, 0xE5, 0x8D, 0x1C,
        0x2A, 0xFC, 0x9C, 0x0B, 0x3C, 0x9D, 0xDD, 0x64, 0xB9, 0x2E, 0x66, 0x51,
        0x40, 0xBC, 0xAF, 0xC9, 0xED, 0xE1, 0x75, 0x1E, 0x58, 0xB0, 0xD4, 0x4F,
        0x97, 0xC1, 0x70, 0xB3, 0xC3, 0x7B, 0x5A, 0xE1, 0xDD, 0x20, 0x2E, 0x38,
        0x83, 0x33, 0x03, 0x0F, 0x0E, 0xDC, 0x00, 0xCB, 0xFE, 0x4C, 0x04, 0xEF,
        0x3A, 0xBE, 0xF5, 0xAA, 0x5C, 0x17, 0x25, 0xF2, 0x88, 0x31, 0x76, 0x8A,
        0x14, 0x69, 0x6A, 0x4B, 0xAF, 0xC1, 0x8B, 0x7A, 0x5B, 0x7C, 0x5C, 0x05,
        0x25, 0x64, 0x80, 0xFE, 0x94, 0xA4, 0xF9, 0x4B, 0xDF, 0x37, 0x62, 0x01,
        0xED, 0xC2, 0xB7, 0xE2, 0x50, 0x88, 0x1E, 0x6F, 0x0B, 0xEA, 0x5B, 0x7B,
        0x13, 0x06, 0x35, 0x1D, 0xD7, 0x29, 0x4E, 0xF9, 0xC1, 0x2F, 0xE9, 0x55,
        0xEA, 0x5D, 0x91, 0xD2, 0x6A, 0x05, 0xF3, 0xF9, 0x69, 0x3F, 0x1B, 0x12,
        0x8D, 0xFD, 0x72, 0xC3, 0x64, 0x1E, 0x35, 0xD0, 0x16, 0x39, 0x04, 0xCA,
        0x2E, 0xD6, 0x3F, 0x33, 0x5C, 0x67, 0xC4, 0x17, 0xA2, 0x8E, 0x30, 0xA3,
        0x95, 0x7F, 0xD0, 0x13, 0x4F, 0xE1, 0xF2, 0x09, 0x0F, 0xC8, 0x8A, 0x46,
        0xAA, 0x50, 0x13, 0xE5, 0xB5, 0xB3, 0xDC, 0x85, 0xDE, 0xA9, 0xEF, 0xC1,
        0x5E, 0x5C, 0xB4, 0xFA, 0xEA, 0x75, 0x07, 0xAA, 0xE2, 0xA4, 0xB6, 0x70,
        0x84, 0xCE, 0x3D, 0x5B, 0x69, 0x95, 0xC5, 0xE8, 0xE9, 0xCC, 0x6D, 0xE1,
        0x03, 0xC9, 0xC9, 0xEA, 0xE9, 0xD5, 0x99, 0x16, 0x2D, 0x75, 0xCE, 0xB5,
        0xF0, 0x48, 0x8A, 0x30, 0xC1, 0xC1, 0xD5, 0xBC, 0xD1, 0xE2, 0xC4, 0x3C,
        0x10, 0xA8, 0x52, 0xE3, 0x88, 0xC6, 0xB0, 0xD6, 0x45, 0x1F, 0x5E, 0x63,
        0x56, 0x38, 0xFF, 0x16, 0x89, 0x19, 0x53, 0x26, 0xD0, 0x5D, 0xCE, 0x71,
        0x13, 0x16, 0x03, 0x65, 0x4A, 0xC8, 0x5C, 0x42, 0xFA, 0xF9, 0xB8, 0xFD,
        0x99, 0x87, 0x64, 0x6B, 0x39, 0xA6, 0xE1, 0x4E, 0xD8, 0x08, 0x6E, 0xEB,
        0x58, 0xA2, 0x88, 0x6A, 0x21, 0x2D, 0x05, 0xA6, 0x29, 0x30, 0xFF, 0x1D,
        0x72, 0x39, 0x41, 0x05, 0x17, 0x89, 0xB8, 0xDE, 0xB6, 0xFA, 0x4E, 0x17,
        0x47, 0x6A, 0x4C, 0xA0, 0x81, 0x3F, 0xE6, 0x63, 0x6C, 0x16, 0x89, 0x70,
        0xAD, 0x28, 0x32, 0x89, 0xB0, 0xEA, 0x4A, 0xEB, 0xCE, 0x9B, 0xA0, 0x10,
        0x63, 0x6D, 0xB4, 0x79, 0x9D, 0x91, 0xCC, 0x69, 0x2E, 0x30, 0x7E, 0xC1,
        0x6E, 0xE5, 0x7E, 0x50, 0x35, 0x57, 0xCE, 0x07, 0x8F, 0xD8, 0x3C, 0xF6,
        0x5A, 0x82, 0xA8, 0xFE, 0xE0, 0x12, 0xD2, 0xEB, 0x9B, 0xDD, 0xFF, 0x75,
        0x67, 0xC9, 0x9E, 0xBD, 0x23, 0xF7, 0xBE, 0xF2, 0xB3, 0x70, 0x98, 0x02,
        0x8B, 0xD0, 0xAB, 0x3A, 0x64, 0x77, 0x39, 0x64, 0x11, 0x34, 0xCE, 0x08,
        0xCF, 0x47, 0xBC, 0x49, 0x04, 0xAC, 0xC3, 0xEB, 0xD4, 0xE3, 0xE2, 0x0D,
        0x37, 0xE4, 0x28, 0x38, 0x53, 0x92, 0x2F, 0x1F, 0xA8, 0x57, 0x2A, 0x3F,
        0x32, 0xDA, 0x1B, 0xB5, 0x86, 0x8E, 0x49, 0xED, 0xAC, 0xF6, 0xC9, 0xD2,
        0x81, 0x73, 0x27, 0xA6, 0xD7, 0x6A, 0xA4, 0x15, 0x57, 0xE6, 0x54, 0xFA,
        0xB8, 0x79, 0x94, 0xB4, 0x95, 0xB1, 0xF4, 0x95, 0x03, 0x17, 0x4F, 0xDB,
        0x14, 0x5A, 0x74, 0x54, 0xBC, 0xC3, 0xB8, 0x02, 0x78, 0x49, 0xA1, 0xFE,
        0xAE, 0x80, 0xAA, 0xAD, 0xED, 0xFC, 0x32, 0x24, 0xC2, 0x0F, 0xBB, 0xF4,
        0x07, 0xA4, 0xF6, 0x87, 0x4C, 0xF2, 0x15, 0x0C, 0xF4, 0xAD, 0x0F, 0x79,
        0x28, 0x8D, 0x76, 0x50, 0xC7, 0x13, 0x96, 0x34, 0x90, 0x6F, 0x70, 0x37,
        0xB6, 0xB5, 0x47, 0xE0, 0xD1, 0x55, 0x29, 0x16, 0x62, 0xE5, 0xC6, 0x46,
        0x94, 0x56, 0x70, 0xCF, 0x4B, 0x78, 0xA3, 0x92, 0xE0, 0x4C, 0xD2, 0x4C,
        0x9D, 0x52, 0x63, 0x3A, 0x39, 0xD9, 0x80, 0xC9, 0xC4, 0x65, 0x6E, 0x91,
        0x1E, 0x2D, 0xEA, 0x27, 0x39, 0x23, 0xAD, 0x77, 0xC2, 0x61, 0x7A, 0x35,
        0x91, 0x3C, 0x6A, 0x13, 0x25, 0xF9, 0x95, 0xDC, 0xB8, 0xAA, 0x8E, 0x8B,
        0x60, 0xAD, 0x2A, 0x6E, 0xD6, 0xCB, 0xEA, 0xC3, 0xDA, 0xC6, 0x73, 0x10,
        0xAA, 0x3D, 0x56, 0x4D, 0x5E, 0x29, 0xD0, 0x1A, 0x54, 0xDA, 0x3F, 0xF2,
        0x44, 0xD7, 0xFB, 0x4F, 0x8C, 0x80, 0x78, 0xD0, 0x7E, 0x9D, 0xDF, 0xA6,
        0x0B, 0xF3, 0x07, 0x3A, 0xBB, 0x15, 0xD2, 0xD4, 0x12, 0x07, 0x50, 0x9E,
        0x87, 0x15, 0x0F, 0x87, 0xB3, 0x99, 0xDF, 0x03, 0x93, 0xA8, 0x69, 0xE1,
        0x7A, 0x02, 0x2A, 0x5D, 0xC3, 0x4E, 0xB4, 0x4A, 0x7C, 0xB2, 0x62, 0xCC,
        0xA2, 0x6C, 0xBA, 0x20, 0x20, 0x75, 0x7A, 0xD8, 0xA6, 0xE0, 0xEF, 0x76,
        0x4D, 0xD7, 0xCF, 0x31, 0xFB, 0xEC, 0x4A, 0xB6, 0x75, 0xB0, 0x0E, 0x94,
        0xCC, 0xE8, 0x49, 0xAB, 0xE4, 0x97, 0x11, 0x70, 0xDF, 0xF8, 0x27, 0xC7,
        0xD1, 0x41, 0xBD, 0x46, 0x57, 0x4B, 0xBC, 0x71, 0x7E, 0xB2, 0x4F, 0x55,
        0xB8, 0x95, 0xB4, 0x12, 0x2D, 0x18, 0x21, 0x98, 0x4E, 0x60, 0xA0, 0x57,
        0x6E, 0x4A, 0xAE, 0x65, 0xE7, 0xE5, 0x97, 0xAD, 0xB1, 0x62, 0xE7, 0x16,
        0x34, 0x8F, 0xFA, 0xFC, 0x54, 0x8F, 0xA1, 0x5C, 0x83, 0xA0, 0x06, 0x34,
        0xA6, 0x94, 0xB1, 0xA1, 0x96, 0xB2, 0x2D, 0x25, 0xD6, 0x0F, 0xEC, 0x43,
        0x29, 0x74, 0x94, 0x26, 0xA2, 0x2F, 0xB1, 0x6C, 0xB2, 0xA4, 0x38, 0x6D,
        0xA9, 0x37, 0x2A, 0x4A, 0x01, 0xD1, 0x6E, 0x6B, 0x37, 0x84, 0x18, 0xFD,
        0x76, 0xCA, 0xD7, 0xED, 0x33, 0x85, 0x30, 0x96, 0x86, 0x8D, 0x5C, 0xC8,
        0x36, 0xBC, 0x79, 0x41, 0x8E, 0x37, 0xF7, 0x35, 0x66, 0xB4, 0x6D, 0x0B,
        0x39, 0xAC, 0x48, 0x1C, 0x96, 0x69, 0x1F, 0x0C, 0xA9, 0x10, 0x58, 0x71,
        0x07, 0xD0, 0xAE, 0x7A, 0x6A, 0x53, 0x3F, 0x10, 0x3F, 0x46, 0xA9, 0x89,
        0x28, 0xDD, 0x25, 0x03, 0x7F, 0xB5, 0x97, 0x5E, 0xB6, 0x9B, 0xFA, 0x4C,
        0x4F, 0x08, 0xE5, 0x24, 0x9D, 0xE5, 0xC9, 0x65, 0x45, 0x29, 0xCD, 0xC4,
        0xC4, 0x84, 0x91, 0x7F, 0x8A, 0xDE, 0xAA, 0xC1, 0x0B, 0xAE, 0xE5, 0x10,
        0xDD, 0xCA, 0xB2, 0x35, 0x11, 0xE2, 0xF5, 0xEA, 0xA6, 0x8C, 0xDE, 0x8F,
        0x77, 0x22, 0xC8, 0x5F, 0x81, 0x11, 0xAD, 0x58, 0x71, 0x0A, 0x71, 0x3D,
        0x2F, 0xC3, 0x10, 0x0B, 0xD6, 0x36, 0xBB, 0x94, 0x09, 0x05, 0xD8, 0x71,
        0x48, 0x2B, 0xD2, 0x44, 0xF3, 0x00, 0x26, 0x18, 0x01, 0x00, 0x00, 0x00,
};

static void test_init_against_reference(void)
{
    isaac_ctx_t ctx;
    memset(ctx.rsl, 0, ISAAC_SIZE);  // Zero seed

    isaac_init(&ctx, true);

    atto_eq(sizeof(ctx), sizeof(expected_initialised_ctx));
    atto_memeq(&ctx, expected_initialised_ctx, sizeof(ctx));
}

void test_isaac_init(void)
{
    test_init_against_reference();
}
