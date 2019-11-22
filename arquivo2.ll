define internal i32 @kempld_gpio_direction_output(%struct.gpio_chip* %chip, i32 %offset, i32 %value) #0 {
entry:
  %chip.addr = alloca %struct.gpio_chip*, align 8
  %offset.addr = alloca i32, align 4
  %value.addr = alloca i32, align 4
  %gpio = alloca %struct.kempld_gpio_data*, align 8
  %pld = alloca %struct.kempld_device_data*, align 8
  store %struct.gpio_chip* %chip, %struct.gpio_chip** %chip.addr, align 8
  store i32 %offset, i32* %offset.addr, align 4
  store i32 %value, i32* %value.addr, align 4
  %0 = load %struct.gpio_chip*, %struct.gpio_chip** %chip.addr, align 8
  %call = call %struct.kempld_gpio_data* @gpiochip_get_data(%struct.gpio_chip* %0)
  store %struct.kempld_gpio_data* %call, %struct.kempld_gpio_data** %gpio, align 8
  %1 = load %struct.kempld_gpio_data*, %struct.kempld_gpio_data** %gpio, align 8
  %pld1 = getelementptr inbounds %struct.kempld_gpio_data, %struct.kempld_gpio_data* %1, i32 0, i32 0
  %2 = load %struct.kempld_device_data*, %struct.kempld_device_data** %pld1, align 8
  store %struct.kempld_device_data* %2, %struct.kempld_device_data** %pld, align 8
  %3 = load %struct.kempld_device_data*, %struct.kempld_device_data** %pld, align 8
  %call2 = call i32 @kempld_get_mutex(%struct.kempld_device_data* %3)
  %4 = load %struct.kempld_device_data*, %struct.kempld_device_data** %pld, align 8
  %5 = load i32, i32* %offset.addr, align 4
  %call3 = call i32 @KEMPLD_GPIO_LVL_NUM(i32 %5)
  %6 = load i32, i32* %offset.addr, align 4
  %7 = load i32, i32* %value.addr, align 4
  %call4 = call i32 @kempld_gpio_bitop(%struct.kempld_device_data* %4, i32 %call3, i32 %6, i32 %7)
  %8 = load %struct.kempld_device_data*, %struct.kempld_device_data** %pld, align 8
  %9 = load i32, i32* %offset.addr, align 4
  %call5 = call i32 @KEMPLD_GPIO_DIR_NUM(i32 %9)
  %10 = load i32, i32* %offset.addr, align 4
  %call6 = call i32 @kempld_gpio_bitop(%struct.kempld_device_data* %8, i32 %call5, i32 %10, i32 1)
  %11 = load %struct.kempld_device_data*, %struct.kempld_device_data** %pld, align 8
  %call7 = call i32 @kempld_release_mutex(%struct.kempld_device_data* %11)
  ret i32 0
}