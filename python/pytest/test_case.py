import pytest

@pytest.fixture
def init_env():
	return 5;

@pytest.mark.test1
def test_square(init_env):
	assert init_env == 5
