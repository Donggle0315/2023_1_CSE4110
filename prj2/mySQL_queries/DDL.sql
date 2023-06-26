CREATE TABLE customer (
    customer_id CHAR(8),
    address VARCHAR(30),
    phone_number CHAR(11),
    PRIMARY KEY (customer_id)
);

CREATE TABLE monthly_contract (
    customer_id CHAR(8),
    contract_date DATE,
    expiry_date DATE,
    account_number CHAR(13),
    PRIMARY KEY (customer_id),
    FOREIGN KEY (customer_id)
        REFERENCES customer (customer_id)
);

CREATE TABLE past_deal (
    customer_id CHAR(8),
    past_year YEAR,
    total_money INT,
    total_count INT,
    PRIMARY KEY (customer_id , past_year),
    FOREIGN KEY (customer_id)
        REFERENCES customer (customer_id)
);

CREATE TABLE service (
    service_type VARCHAR(10),
    packing_type VARCHAR(5),
    weight INT,
    delivery_type VARCHAR(10),
    charge INT,
    PRIMARY KEY (service_type)
);

CREATE TABLE package (
    package_id CHAR(8),
    state VARCHAR(10),
    destination_address VARCHAR(30),
    expected_arrive_date DATE,
    actual_arrive_date DATE,
    customer_id CHAR(8),
    service_type VARCHAR(10),
    PRIMARY KEY (package_id),
    FOREIGN KEY (customer_id)
        REFERENCES customer (customer_id),
    FOREIGN KEY (service_type)
        REFERENCES service (service_type)
);

CREATE TABLE take_back (
    refund_state INT,
    pay_done BOOL,
    picked_up BOOL,
    PRIMARY KEY (refund_state)
);

CREATE TABLE refund (
    package_id CHAR(8),
    refund_state INT,
    PRIMARY KEY (package_id),
    FOREIGN KEY (package_id)
        REFERENCES package (package_id),
    FOREIGN KEY (refund_state)
        REFERENCES take_back (refund_state)
);

CREATE TABLE product (
    product_id CHAR(8),
    PRIMARY KEY (product_id)
);

CREATE TABLE packing (
    package_id CHAR(8),
    product_id CHAR(8),
    registration BOOL,
    PRIMARY KEY (package_id, product_id),
    FOREIGN KEY (package_id)
        REFERENCES package (package_id),
    FOREIGN KEY (product_id)
        REFERENCES product (product_id)
);


CREATE TABLE content (
    product_id CHAR(8),
    product_type VARCHAR(10),
    product_content VARCHAR(10),
    PRIMARY KEY (product_id),
    FOREIGN KEY (product_id)
        REFERENCES product (product_id)
);

CREATE TABLE shipment (
    vehicle VARCHAR(10),
    vehicle_id CHAR(8),
    is_running VARCHAR(10),
    PRIMARY KEY (vehicle , vehicle_id)
);

CREATE TABLE loading (
    package_id CHAR(8),
    vehicle_id CHAR(8),
    vehicle VARCHAR(10),
    is_visited BOOL,
    priority_order INT,
    PRIMARY KEY (package_id),
    FOREIGN KEY (package_id)
        REFERENCES package (package_id),
    FOREIGN KEY (vehicle, vehicle_id)
        REFERENCES shipment (vehicle, vehicle_id)
);




